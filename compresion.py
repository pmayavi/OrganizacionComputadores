class Node:
    def __init__(self, nsize, uses, char_element, parent=None, left=None, right=None):
        self.data_element = nsize
        self.uses = uses
        self.char_element = char_element
        self.parent = parent
        self.left = left
        self.right = right

codes = dict()

def insert(parent, node, nsize):
    if (parent.char_element != 0):
        return
    if (not parent.right):
        parent.right = node
        node.parent = parent
        nsize -= 1
        parent.left = Node(nsize, 0, 0)
        parent.left.parent = parent
    else:
        insert(parent.left, node, nsize)
        insert(parent.right, node, nsize)

def exchange(node, objective):
    print('Exchange:', node.data_element, objective.data_element)
    print('1:', node.parent.left.data_element, node.parent.right.data_element)
    
    if (node.parent.right.data_element == objective.data_element):
        node.parent.right = node
        node.parent.left = objective
    else:
        node.parent.left = node
        node.parent.right = objective
        
    print('2:', node.parent.left.data_element, node.parent.right.data_element)
    
    ParentValue(objective)
    ParentValue(node)

def ParentValue(node):
    Lchild = 0
    Rchild = 0
    if (node.left):
        Lchild = node.left.uses
    if (node.left):
        Rchild = node.right.uses
    if (Lchild + Rchild > 0):
        node.uses = Lchild + Rchild
    if (node.parent):
        ParentValue(node.parent)

def compare(node):
    temp = node.parent
    ex1 = None
    ex2 = None
    if (temp.parent): 
        while True:
            if temp.parent.right.data_element != temp.data_element:
                temp = temp.parent
                if (temp.left.uses > temp.right.uses):
                    print(temp.left.uses, '>', temp.right.uses, temp.right.char_element, 'right')
                    ex1 = temp.right
                    ex2 = temp.left
                if (not temp.parent): 
                    break
            else:
                temp = temp.parent
                if (temp.right.uses > temp.left.uses):
                    print(temp.right.uses, '>', temp.left.uses, temp.left.char_element, 'left')
                    ex1 = temp.left
                    ex2 = temp.right
                if (not temp.parent): 
                    break
        if (ex1 and ex2):
            exchange(ex2, ex1)
            ParentValue(node)
            ParentValue(ex1)

def print_nodes(node, code=''):
    if (node.char_element):
        print(node.char_element, node.uses, node.data_element, code)
    if (node.right):
        print_nodes(node.right, code + '1')
    if (node.left):
        print_nodes(node.left, code +'0')

def Calcular_Codigos(node, val=''):
    if(node.right):
        Calcular_Codigos(node.right, val + '1')
    if(node.left):
        Calcular_Codigos(node.left, val + '0')
    if(not node.left and not node.right):
        codes[node.char_element] = val  

def Codificacion_Output(data, coding):
    output = []
    for c in data:
        output.append(coding[c])
    
    string = ''.join([str(o) for o in output])    
    return string      

COUNT = [10]
def print2DUtil(root, space):
 
    # Base case
    if (root == None):
        return
 
    # Increase distance between levels
    space += COUNT[0]
 
    # Process right child first
    print2DUtil(root.right, space)
 
    # Print current node after space
    # count
    print()
    for i in range(COUNT[0], space):
        print(end=" ")
    print(root.char_element)
 
    # Process left child
    print2DUtil(root.left, space)

def Codificacion_Huffman(data):
    N = 107
    nsize = (2 * N) - 1
    #inp = input()
    inp = data
    letters = dict()
    tree = dict()
    root = Node(nsize, 0, 0)
    nsize -= 1
    for i in inp:
        new = True
        # Poner aqui el rango de chars, print("Simbolo encontrado genera error de compresion");
        if letters.get(i):
            letters[i] += 1
            node = tree.get(i)
            node.uses += 1
            ParentValue(node)
            compare(node)
            #print2DUtil(root, 0)
        else: 
            letters[i] = 1
            newNode = Node(nsize, 1, i)
            insert(root, newNode, nsize)    
            tree[i] = newNode
            nsize -= 2
    
    Calcular_Codigos(root)
    encoding = Codificacion_Output(data,codes)
    print("Output", encoding)
    print_nodes(root)

data = "AAAAAAABCCCCCCDDEEEEE"
print(data)
Codificacion_Huffman(data)