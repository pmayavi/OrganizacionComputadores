# Compresion de archivos por medio del Huffman adaptativo
## Practica 3 Organizacion de Computadores
### Noviembre 2022
### Profesor Jose Luis Montoya Pareja
### Universidad EAFIT
***
#### Pablo Maya Villegas
#### Andres Echeverri Jaramillo
#### Salomon Velez Perez
***

Hecho en Python3.11 compilado con auto-py-to-exe 2.24.1

[Sustentacion en Youtube]()

### Descripcion del proyecto:
Nuestro codigo va generando un arbol binario el cual puede ser re-balanceado con cada letra nueva que lee, es distinto a los algoritmos Huffman que vimos en internet ya que el arbol generado es casi que lineal y lo decidimos dejar asi porque es el algoritmo especifico que aprendimos en clase.
El archivo exe debe ser llamado de la forma _start compresion.exe texto.txt n_ con n siendo el numero de threads deseadas, y dentro del archivo texto.txt estaria la string a comprimir, esta string debe tener caracteres en el rango ASCII de 32-127 mas las vocales tildadas y las ñ, asi que por ejemplo, no puede haber enters o lineas nuevas (\n) ya que este caracter tiene el codigo ASCII de 13.
Al llamar correctamente al exe, se divide la string a comprimir en n partes y las distribuye a las threads, cada thread genera su propio arbol y entrega al usuario ese segmento comprimido.
#### Generacion del arbol
Al encontrar un caracter nuevo genera dos hijos en el nodo NYT actual, el cual es el nuevo NYT a la izquierda y el caracter a la derecha.
Al encontrar un caracter que ya existe en el arbol, le suma 1 a su numero de usos y se comprueba si se debe re-balancear el arbol:
 - Compara cada padre del node con su hermano, de forma que el mas pesado entre ellos este a la derecha.
 - Compara el node actualizado con las otras hojas del arbol que esten por encima de el, si es mayor que una de estas se intercambian sus posiciones.
