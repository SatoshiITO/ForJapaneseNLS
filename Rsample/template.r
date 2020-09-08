SIM.para <- matrix(rnorm(100,0,1), ncol=10)
SIM.para[,1] <-c(1:10)
params <- SIM.para[jobID+1,]

###write.table(rate.1,paste("SIMULATION.K/",5,"_SM.T4.L.5.txt",sep=""),row.names=FALSE,col.names=FALSE,sep="\t",quote=FALSE)
write.table(params,"result.txt",sep="\t")
