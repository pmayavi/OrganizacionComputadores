# adaptado de https://github.com/YCAyca/Data-Structures-and-Algorithms-with-Python/tree/main/Huffman_Encoding
class Node:
    def __init__(self, prob, simb, left=None, right=None):
        self.prob = prob
        self.simb = simb
        self.left = left
        self.right = right
        self.code = ''

codes = dict()

def Calcular_Codigos(node, val=''):
    val2 = val + str(node.code)
    if(node.left):
        Calcular_Codigos(node.left, val2)
    if(node.right):
        Calcular_Codigos(node.right, val2)
    if(not node.left and not node.right):
        codes[node.simb] = val2  
    return codes        

def Calcular_Probabilidad(data):
    simbs = dict()
    for d in data:
        if simbs.get(d) == None:
            simbs[d] = 1
        else: 
            simbs[d] += 1     
    return simbs

def Codificacion_Output(data, coding):
    output = []
    for c in data:
        output.append(coding[c])
        
    string = ''.join([str(o) for o in output])    
    return string       

def Codificacion_Huffman(data):
    simb_probs = Calcular_Probabilidad(data)
    simbs = simb_probs.keys()
    probs = simb_probs.values()
    print("Simbolos: ", simbs)
    print("Probabilidades: ", probs)
    
    nodes = []
    for simb in simbs:
        nodes.append(Node(simb_probs.get(simb), simb))
    
    while len(nodes) > 1:
        nodes = sorted(nodes, key=lambda x: x.prob)

        right = nodes[0]
        left = nodes[1]
    
        left.code = 0
        right.code = 1
    
        newNode = Node(left.prob+right.prob, left.simb+right.simb, left, right)
    
        nodes.remove(left)
        nodes.remove(right)
        nodes.append(newNode)
            
    codificacion = Calcular_Codigos(nodes[0])
    print("Simboloss con codigos", codificacion)
    encoded_output = Codificacion_Output(data,codificacion)
    return encoded_output, nodes[0]  

data = "AAAAAAABCCCCCCDDEEEEE"
print(data)
encoding, tree = Codificacion_Huffman(data)
print("Output", encoding)