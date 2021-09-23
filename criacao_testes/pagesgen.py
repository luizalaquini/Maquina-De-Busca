from random import seed
from random import randint

fileNum = 1000

#Get a .txt file
ffrom = open("got.txt", "r")

texto = ffrom.read()

#remove all the ponctuations
punc = '''!()[]{};:'"\,<>./?@#$%^&*_~'''
for elem in punc:
    texto = texto.replace(elem, "")
texto = texto.replace('“', "")
texto = texto.replace('”', "")

ffrom2 = open("got_clean.txt", "w")
ffrom2.write(texto)

ffrom2 = open("got_clean.txt", "r")


#divide equally into 5000 files
for page in range(fileNum):
    fout = open("pages/"+str(page)+".txt", "w")
    for line in range(54):
        fout.write(ffrom2.readline())

findex = open("index.txt", "w")
for i in range(fileNum):
    findex.write(str(i)+".txt\n")


#Create graph
fgraph = open("graph.txt", "w")
for i in range(fileNum):
    # seed random number generator
    seed(i)
    # generate some random numbers
    linkNum = randint(0, 20)
    fgraph.write(str(i)+".txt "+str(linkNum)+" ")
    for link in range(linkNum):
        fgraph.write(str(randint(0, fileNum-1))+".txt ")
    fgraph.write("\n")

