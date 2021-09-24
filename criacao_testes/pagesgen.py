from random import seed
from random import randint

fileNum = 5000

#Get a .txt file
ffrom1 = open("books/bible.txt", "r")
ffrom2 = open("books/got.txt", "r")
ffrom3 = open("books/Mockingjay.txt", "r")
ffrom4 = open("books/alice29.txt", "r")
ffrom5 = open("books/asyoulik.txt", "r")
ffrom6 = open("books/book1", "r")
ffrom7 = open("books/book2", "r")
ffrom8 = open("books/got2.txt", "r")
ffrom9 = open("books/got3.txt", "r")

ffrom = open("appended.txt", "w")
text = ffrom1.read() + ffrom2.read() + ffrom3.read() + ffrom4.read() + ffrom5.read() + ffrom6.read() + ffrom7.read() + ffrom8.read() + ffrom9.read()
text = text + text
text += text
ffrom.write(text)

ffrom.close()
ffrom = open("appended.txt", "r")
texto = ffrom.read()


#remove all the ponctuations
punc = '''!()[]{};:'"\,<>./?@#$%^&*_~'''
for elem in punc:
    texto = texto.replace(elem, "")
texto = texto.replace('“', "")
texto = texto.replace('”', "")

ffrom2 = open("appended_clean.txt", "w")
ffrom2.write(texto)

ffrom2 = open("appended_clean.txt", "r")


#divide equally into 5000 files
for page in range(fileNum):
    fout = open("pages/"+str(page)+".txt", "w")
    for line in range(100):
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

