set.seed(123456)

m <- 5000
n <- 2000

x <- matrix(rnorm(m*n),m,n)
y <- matrix(rnorm(m*n),n,m)
z <- matrix(rnorm(n*n),n,n)

T1 <- Sys.time()
svdx <- svd(x)
T2 <- Sys.time()

T2 - T1

T3 <- Sys.time()
xy <- x%*%y
T4 <- Sys.time()

T4 - T3

T5 <- Sys.time()
invz <- solve(z)
T6 <- Sys.time()

T6 - T5
