import json
import time
import threading

class myThread (threading.Thread):
   def __init__(self, threadID, name,string):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.string=string
   def run(self):
      print ("Starting " + self.name)
      threadLock.acquire()
      Codificacion_Huffman(string, self.name)
      threadLock.release()

class Node:
    def __init__(self, nsize, uses, char_element, parent=None, left=None, right=None):
        self.num = nsize
        self.uses = uses
        self.char_element = char_element
        self.parent = parent
        self.left = left
        self.right = right

codes = dict()
NYT = ['']
with open('letras.json', encoding="utf8") as json_file:
    Letras = json.load(json_file)

def insert(parent, node, nsize, val=''):
    if (parent.char_element != 0):
        return
    if (not parent.right):
        parent.right = node
        node.parent = parent
        nsize -= 1
        parent.left = Node(nsize, 0, 0)
        parent.left.parent = parent
        NYT[0] = val + '0'
    else:
        insert(parent.left, node, nsize, val + '0')
        insert(parent.right, node, nsize, val + '1')

def SwapHermanos(node, objective):
    if (node.parent.right.num == objective.num):
        node.parent.right = node
        node.parent.left = objective
    else:
        node.parent.left = node
        node.parent.right = objective
    
    temp = node.num
    node.num = objective.num
    objective.num = temp
    
    ParentValue(objective)
    ParentValue(node)

def SwapNodes(node, objective):
    temp = node.parent
    node.parent = objective.parent
    if (node.parent.right.num == objective.num):
        node.parent.right = node
    else:
        node.parent.left = node
    
    objective.parent = temp
    if (objective.parent.right.num == node.num):
        objective.parent.right = objective
    else:
        objective.parent.left = objective
    
    temp = node.num
    node.num = objective.num
    objective.num = temp
    
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

def CompareHermanos(node):
    temp = node.parent
    ex1 = None
    ex2 = None
    if (temp.parent): 
        while True:
            if temp.parent.right.num != temp.num:
                temp = temp.parent
                if (temp.left.num < temp.right.num and temp.left.uses > temp.right.uses):
                    ex1 = temp.right
                    ex2 = temp.left
            else:
                temp = temp.parent
                if (temp.left.num > temp.right.num and temp.right.uses > temp.left.uses):
                    ex1 = temp.left
                    ex2 = temp.right
            if (not temp.parent): 
                break
        if (ex1 and ex2):
            SwapHermanos(ex2, ex1)
            ParentValue(node)
            ParentValue(ex1)

def CompareNodes(node):
    temp = node.parent
    if temp and temp.parent:
        ex = None
        while True:
            temp = temp.parent
            if (temp.right and temp.parent and not temp.right.right and temp.right.char_element != 0 and node.uses > temp.right.uses and temp.parent.right.num != temp.num):
                ex = temp.right
            if (temp.left and temp.parent and not temp.left.right and temp.left.char_element != 0 and node.uses > temp.left.uses and temp.parent.left.num != temp.num):
                ex = temp.left
            if (not temp.parent):
                break
        if (ex and node.num != ex.num):
            SwapNodes(node, ex)

def print_nodes(node, code=''):
    if (node.char_element):
        print(node.char_element, node.uses, node.num, code)
    if (node.left):
        print_nodes(node.left, code +'0')  
    if (node.right):
        print_nodes(node.right, code + '1')

def Calcular_Codigos(node, val=''):
    if(node.right):
        Calcular_Codigos(node.right, val + '1')
    if(node.left):
        Calcular_Codigos(node.left, val + '0')
    if(not node.left and not node.right):
        codes[node.char_element] = val  

def Codificacion_Output(data, coding, NYTs):
    output = []
    letters = dict()
    count = -1
    for c in data:
        if letters.get(c):
            output.append(coding[c] + ' ')
        else:
            letters[c] = 1
            if count >= 0:
                output.append(NYTs[count] + ' ')
            count += 1
            if (c == ' '):
                output.append("0000000" + ' ')
            else: 
                output.append(Letras[c] + ' ')
    
    string = ''.join([str(o) for o in output])    
    return string      

COUNT = [10]
def print2DUtil(root, space):
    if (root == None):
        return
    space += COUNT[0]
    print2DUtil(root.right, space)
    print()
    for i in range(COUNT[0], space):
        print(end=" ")
    print2DUtil(root.left, space)


def Codificacion_Huffman(data,name):
    N = 107
    nsize = (2 * N) - 1
    #inp = input()
    NYTlist = []
    inp = data
    letters = dict()
    tree = dict()
    root = Node(nsize, 0, 0)
    nsize -= 1
    error = False
    for i in inp:
        if (not Letras.get(i)) and i != ' ':
            print("Simbolo encontrado genera error de compresion")
            return
        # Poner aqui el rango de chars, print("Simbolo encontrado genera error de compresion");
        if letters.get(i):
            letters[i] += 1
            node = tree.get(i)
            node.uses += 1
            ParentValue(node)
            CompareNodes(node)
            CompareHermanos(node)
        else: 
            letters[i] = 1
            newNode = Node(nsize, 1, i)
            insert(root, newNode, nsize) 
            NYTlist.append(NYT[0])
            tree[i] = newNode
            nsize -= 2
    
    Calcular_Codigos(root)
    #print(letters)
    #print(codes)
    encoding = Codificacion_Output(data,codes, NYTlist)
    print(name,": ",encoding)
    #print_nodes(root)


def crearhilo(nombre,data,id):
    thread=myThread(id,nombre,data)
    thread.start()
    return thread

threadLock = threading.Lock()
data = "aabcdad"
length = len(data)   
n = 3 
chars = int(length/n)
temp=0
threads = []
m=1
print(data)
while n>0:
    if n>1:
        string=data[temp:temp+chars]
        temp=temp+chars
        n=n-1
        threads.append(crearhilo("thread "+str(m),string,m))
        m=m+1
    else:
        string=data[temp:]
        temp=temp+chars
        n=n-1
        threads.append(crearhilo("thread "+str(m),string,m))
        m=m+1
time.sleep(100)