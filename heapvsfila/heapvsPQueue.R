data <- read.csv("temp.csv", header=TRUE)

plot(data$HEAP, type="o", xaxt = "n", col="red", ann=FALSE)

axis(1, at=1:1000, data$N_ELEMENTS)
box()

lines(data$P_QUEUE, type="o", col="blue")

title(main="heap vs p_queue", col.main="black", font.main=4)
title(xlab="quantidade de Valores", col.lab=rgb(0,0.5,0))
title(ylab="Comparações", col.lab=rgb(0,0.5,0))
title(main="heap vc fila de prioridade", col.main="black", font.main=4)


