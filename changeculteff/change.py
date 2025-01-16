import os
import sys
import re
import chardet

def open_with_detected_encoding(file_path, mode='r'):
	"""
	Opens a file with automatic encoding detection.
	
	Args:
		file_path (str): Path to the file to open.
		mode (str): File open mode (default is 'r' for reading).
	
	Returns:
		file object: Open file object.
	"""
	with open(file_path, 'rb') as file:
		raw_data = file.read()
		result = chardet.detect(raw_data)
		encoding = result['encoding']
		if not encoding:
			encoding='utf-8'
	
	# Open the file with the detected encoding
	return open(file_path, mode, encoding=encoding)

def output_assimilation_modifiers(modifier_dict, path="acr_conv_modifiers.txt"):
	reference_mods = []
	if os.path.exists(path) and os.path.isfile(path):
		with open(path, 'r', encoding='utf-8') as f:
			i = 0
			lines = f.readlines()
			while i < len(lines):
				reference_mods.append(lines[i].split()[0])
				i += 3
	
	with open(path, 'a', encoding='utf-8') as f:
		for k, v in modifier_dict.items():
			if k not in reference_mods:
				f.write(f"{k} = {{\n\t{v}\n}}\n")
			
	return reference_mods

def process_files_in_directory(directory, idmap):
	# Define the regex pattern to match the target lines
	modifiers = {}
	modifier_list = []
	pattern = re.compile(r"^(\s*)change_culture = ([\w:]+)")

	# Iterate through all files in the directory
	for i, filename in enumerate(os.listdir(directory)):
		print(f"{i} Processing {filename}")
		file_path = os.path.join(directory, filename)

		# Ensure we're working with files only
		if not os.path.isfile(file_path):
			continue

		with open_with_detected_encoding(file_path, 'r') as file:
			lines = file.readlines()

		# List to hold modified lines
		new_lines = []
		
		# Process each line in the file
		for line in lines:
			match = pattern.match(line)
			if match:
				indentation, culture_name = match.groups()
				if culture_name not in idmap:
					continue
				culture_name = culture_name.strip().split(':')[-1]
				modifiers[f"acr_{culture_name}_assimilates"] = "picture = pop_colonial_immigrants"
				new_lines.append(f"{indentation}add_province_modifier = {{ name = acr_{culture_name}_assimilates duration = 3650 hidden = yes }}\n")
			else:
				new_lines.append(line)

		# Write the modified lines back to the file
		with open(file_path, 'w') as file:
			file.writelines(new_lines)
		modifier_list.extend(output_assimilation_modifiers(modifiers))
	return modifier_list

def parse_culture_ids(path="CULTURE_IDS.txt"):
	idmap = {}
	with open(path, 'r', encoding='utf-8') as f:
		for line in f:
			tokens = line.strip().split('\t')
			idmap[tokens[1]] = tokens[0]
	return idmap

if __name__ == "__main__":
	idmap = parse_culture_ids()
	i = 1
	modifier_list = []
	while i < len(sys.argv):
		modifier_list.extend(process_files_in_directory(sys.argv[i], idmap))
		i += 1
	
