data <- read.csv("temp.csv", header=TRUE)

plot(data$BST, type="o", xaxt = "n", col="red", ann=FALSE)

axis(1, at=1:100, data$SEARCHES)
box()

lines(data$AVL, type="o", col="blue")

title(main="avl vs bst", col.main="black", font.main=4)
title(xlab="quantidade de Valores", col.lab=rgb(0,0.5,0))
title(ylab="Comparações", col.lab=rgb(0,0.5,0))
title(main="avl vs Árvore de Busca Binária", col.main="black", font.main=4)


