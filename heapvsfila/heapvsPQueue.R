data <- read.csv("temp.csv", header=TRUE)


plot(data$P_QUEUE, type="l", xaxt = "n", col="red", ann=FALSE)

axis(1, at=1:100, data$N_ELEMENTS)
box()

lines(data$HEAP, type="l", col="blue")

title(xlab="quantidade de Valores", col.lab=rgb(0,0.5,0))
title(ylab="Comparações", col.lab=rgb(0,0.5,0))
title(main="heap vs fila de prioridade", col.main="black", font.main=4)


