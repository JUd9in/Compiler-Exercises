import re
s="\"they are closed.\""
pattern=re.compile(r'(.*) are (.*)')
p2=re.compile(r'(?<=")([a-zA-Z\s]+[\.])(?=")')
print(p2.findall(s))
lst=pattern.findall(s)
print(lst)