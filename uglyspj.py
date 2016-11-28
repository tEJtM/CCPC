import sys
f = open(sys.argv[1], "r")
g = open(sys.argv[2], "r")
tests = eval(f.readline())
flag = True
for test in range(tests) :
	a = eval(f.readline())
	str = g.readline()
	if str.strip('\n').strip('\r') != "Case #%d:" % (test + 1) :
		flag = False
		break
	n = eval(g.readline())
	tot = 0

	for i in range(n) :
		if n > 70 :
			flag = False
			break
		x = g.readline()
		x = x.strip('\n').strip('\r')
		if len(x) > 1000 :
			flag = False
			break
		#print x, '?', x[::-1]
		if x != x[::-1] :
			flag = False
			break
		if x[0] == '0' :
			flag = False
			break
		for j in range(len(x)) :
			if x[j] < '0' or x[j] > '9' :
				flag = False
				break
		tot = tot + eval(x)
		#print tot, eval(x)
		#print flag
	#print tot, a
	if tot != a :
		flag = False
		break
	#print flag
if flag :
	print "OK"
else :
	print "WA"
