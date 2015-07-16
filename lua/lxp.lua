--lxp.
business = false 
frames = { "app","access-dispatcher","logic","storage" }
langs = { "c++","python","html","lua","php","mysql" }
--setmetatable(frames, {__index=langs})
attrs = {}
function attrs.__add(x,y)
	res = {}
	for k,v in pairs(x) do res[k]=v end
	for k,v in pairs(y) do res[k*10]=v end --not res[k], for index overlap
	return res
end
setmetatable(frames, attrs)
setmetatable(langs, attrs)


learn_times = 0
change_index = 10

while(not business) do
	learn_times = learn_times + 1
	if (learn_times == change_index) then
		print "tech -> business. ["

		for k,v in pairs(frames+langs) do
			print(" ", v)
		end

		print "]"
		break
	end
	print "tech."
end
