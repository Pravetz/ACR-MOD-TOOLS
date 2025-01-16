import os
import sys

def load_modifiers(path):
	reference_mods = []
	if os.path.exists(path) and os.path.isfile(path):
		with open(path, 'r', encoding='utf-8') as f:
			i = 0
			lines = f.readlines()
			while i < len(lines):
				reference_mods.append(lines[i].split()[0])
				i += 3
	
	return reference_mods

def load_template(path):
	data = { "namespace" : "", "evt_body" : "" }
	
	with open(path, 'r', encoding='utf-8') as templ:
		data["namespace"] = templ.readline()
		data["evt_body"] = ''.join(templ.readlines())
	
	return data

def parse_culture_ids(path="CULTURE_IDS.txt"):
	idmap = {}
	with open(path, 'r', encoding='utf-8') as f:
		for line in f:
			tokens = line.strip().split('\t')
			idmap[tokens[1]] = tokens[0]
	return idmap

def extract_culture_name_from_modifier(modifier):
	return modifier.replace('acr_', '').replace('_assimilates', '')

def replace_templates(template_string, modifier, culture, culture_id):
	return template_string.replace('%CULTURE%', culture).replace('%MODIFIER%', modifier).replace('%CULTURE_ID%', culture_id)

def mkevents(path, template, modifiers, culture_ids):
	for modifier in modifiers:
		culture = extract_culture_name_from_modifier(modifier)
		with open(os.path.join(path, f"{modifier}_event.txt"), 'w', encoding='utf-8') as evt:
			evt.write(replace_templates(template["namespace"], modifier, culture, str(culture_ids[culture])))
			evt.write(replace_templates(template["evt_body"], modifier, culture, str(culture_ids[culture])))
			
			
	
	

if __name__ == "__main__":
	template = load_template(sys.argv[1])
	modifiers = load_modifiers(sys.argv[2])
	culture_ids = parse_culture_ids(sys.argv[3])
	output_path = sys.argv[4]
	
	mkevents(output_path, template, modifiers, culture_ids)