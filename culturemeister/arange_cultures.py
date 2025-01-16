import sys
import re


def parse_data(file_content):
	content = re.sub(r"#.*", "", file_content)
	
	def parse_block(lines):
		data = {}
		stack = [data]
		current_key = None
	
		for line in lines:
			line = line.strip()
			if not line:
				continue
	
			kv_match = re.match(r"(\w+)\s*=\s*(.*)", line)
			if kv_match:
				key, value = kv_match.groups()
				if value == "{":
					if key in ["male_names", "female_names", "dynasty_names"]:
						new_block = []
					else:
						new_block = {}
					stack[-1][key] = new_block
					stack.append(new_block)
					current_key = key
				elif value.startswith("{") and value.endswith("}"):
					items = value[1:-1].split()
					stack[-1][key] = items
					current_key = key
				else:
					stack[-1][key] = value
					current_key = key
			elif line == "}":
				if len(stack) > 1:
					stack.pop()
					current_key = None
				else:
					raise ValueError("Unmatched closing '}' encountered.")
			else:
				if current_key and isinstance(stack[-1], list):
					stack[-1].extend(line.split())
				else:
					raise ValueError(f"Unexpected continuation line: {line}")
	
		return data
	
	lines = content.splitlines()
	return parse_block(lines)

def output_to_file(data, path):
	with open(path, 'w', encoding='iso-8859-1') as out:
		for group, cultures in data.items():
			out.write(f"{group} = {{\n")
			for culture, data in cultures.items():
				if culture in ["graphical_culture", "second_graphical_culture", "primary"]:
					out.write(f"\t{culture} = {data}\n")
					continue
				if culture in ["female_names", "male_names", "dynasty_names"]:
					out.write(f"\t{culture} = {{\n\t\t")
					for i, name in enumerate(data):
						out.write(f"{name}{'\n\t\t' if i != 0 and i % 10 == 0 else ' '}")
					out.write("\n\t}\n")
					continue
				if culture in ["country", "province"]:
					out.write(f"\t{culture} = {{\n\t\t")
					for d in data:
						out.write(f"{d} ")
					out.write("\n\t}\n")
					continue
				
				out.write(f"\t{culture} = {{\n")
				for k, v in data.items():
					if k in ["graphical_culture", "second_graphical_culture", "primary"]:
						out.write(f"\t\t{k} = {v}\n")
						continue
					if k in ["female_names", "male_names", "dynasty_names"]:
						out.write(f"\t\t{k} = {{\n\t\t\t")
						for i, name in enumerate(v):
							out.write(f"{name}{'\n\t\t\t' if i != 0 and i % 10 == 0 else ' '}")
						out.write("\n\t\t}\n")
						continue
					if k in ["country", "province"]:
						out.write(f"\t\t{k} = {{\n\t\t\t")
						for d in v:
							out.write(f"{d} ")
						out.write("\n\t\t}\n")
						continue
				out.write("\t}\n")
			out.write("}\n\n")

def move_cultures(data, directives):
	for directive in directives:
		if len(directive) != 3:
			continue
		else:
			if directive[1] in data[directive[0]]:
				culture_data = data[directive[0]].pop(directive[1])
				data[directive[2]][directive[1]] = culture_data

if __name__ == "__main__":
	i = 1
	
	files = []
	replacements = []
	output = ""
	while i < len(sys.argv):
		if sys.argv[i] == "-i" and i + 1 < len(sys.argv):
			files.append(sys.argv[i + 1])
			i += 1
		elif sys.argv[i] == "-o" and i + 1 < len(sys.argv):
			output = sys.argv[i + 1]
			i += 1
		else:
			tokens = re.split(r"[,. >]+", sys.argv[i].strip())
			replacements.append(tokens)
		i += 1
	
	file_path = sys.argv[1]
	parsed_files = []
	for file_path in files:
		with open(file_path, 'r', encoding='iso-8859-1') as file:
			file_content = file.read()
		parsed_data = parse_data(file_content)
		parsed_files.append(parsed_data)
	output_data = {}
	culture_counts = {}
	for parsed in parsed_files:
		for k, v in parsed.items():
			if k in output_data:
				for kk, kv in v.items():
					if kk not in output_data[k]:
						output_data[k][kk] = kv
			else:
				output_data[k] = v
	
	print(replacements)
	move_cultures(output_data, replacements)
	for _, data in output_data.items():
		for k, v in data.items():
			if k in ["female_names", "male_names", "dynasty_names", "graphical_culture", "second_graphical_culture", "primary", "country", "province"]:
				continue
			if k not in culture_counts:
				culture_counts[k] = 1
			else:
				culture_counts[k] += 1
	print('\n',culture_counts)
	
	output_to_file(output_data, output)
	