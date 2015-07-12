import md5

class HashRing(object):

    def __init__(self, nodes=None, replicas=3):
        """Manages a hash ring.

        `nodes` is a list of objects that have a proper __str__ representation.
        `replicas` indicates how many virtual points should be used pr. node,
        replicas are required to improve the distribution.
        """
        self.replicas = replicas

        self.ring = dict()
        self._sorted_keys = []

        if nodes:
            for node in nodes:
                self.add_node(node)
        print '+show shorted keys: \n ','\n  '.join([str(x) for x in self._sorted_keys])

    def add_node(self, node):
        """Adds a `node` to the hash ring (including a number of replicas).
        """
        for i in xrange(0, self.replicas):
            key = self.gen_key('%s:%s' % (node, i))
            self.ring[key] = node
            self._sorted_keys.append(key)
	    #print '+insert: ',i,key

        self._sorted_keys.sort()

    def remove_node(self, node):
        """Removes `node` from the hash ring and its replicas.
        """
        for i in xrange(0, self.replicas):
            key = self.gen_key('%s:%s' % (node, i))
            print "+ ", '%s:%s' % (node, i), key
            del self.ring[key]
            self._sorted_keys.remove(key)

    def get_node(self, string_key):
        """Given a string key a corresponding node in the hash ring is returned.

        If the hash ring is empty, `None` is returned.
        """
        return self.get_node_pos(string_key)[0]

    def get_node_pos(self, string_key):
        """Given a string key a corresponding node in the hash ring is returned
        along with it's position in the ring.

        If the hash ring is empty, (`None`, `None`) is returned.
        """
        if not self.ring:
            return None, None

        key = self.gen_key(string_key)
	print '+gen_key: ',string_key,key

        nodes = self._sorted_keys
        for i in xrange(0, len(nodes)):
            node = nodes[i]
            if key <= node:
                return self.ring[node], i

        return self.ring[nodes[0]], 0

    def get_nodes(self, string_key):
        """Given a string key it returns the nodes as a generator that can hold the key.

        The generator is never ending and iterates through the ring
        starting at the correct position.
        """
        if not self.ring:
            yield None, None

        node, pos = self.get_node_pos(string_key)
        for key in self._sorted_keys[pos:]:
            yield self.ring[key]

        while True:
            for key in self._sorted_keys:
                yield self.ring[key]

    def gen_key(self, key):
        """Given a string key it returns a long value,
        this long value represents a place on the hash ring.

        md5 is currently used because it mixes well.
        """
        m = md5.new()
        m.update(key)
        return long(m.hexdigest(), 16)

def print_ring(desc):
    print "\nstart [%s]. "%desc
    for k,v in ring.ring.items():
        print " ",k,v
    print "end. \n"


memcache_servers = ['192.168.0.1:11212',
                    '192.168.0.2:11212']

ring = HashRing(memcache_servers)
print_ring("before add")
ring.add_node('192.168.0.3:11212')
print_ring("after add")

server = ring.get_node('my_key')
print '+try get server: ',server
server = ring.get_node('my_key2')
print '+try get server: ',server
server = ring.get_node('my_key3')
print '+try get server: ',server
#print '\n+before remove node: \n','\n'.join( [str(x) for x in ring.ring.keys()] )
print_ring("before remove")
ring.remove_node('192.168.0.2:11212')
print_ring("after remove")
#print '\n+after remove node: \n','\n'.join( [str(x) for x in ring.ring.keys()] )



