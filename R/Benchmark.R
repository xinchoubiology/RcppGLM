##' function of benchmark subset
##'
##' @title mm_benchmark
##' @param size scale of tested matrix; default 10
##' @return NULL
##' @export
##' @author xin zhou \url{xxz220@@miami.edu}
mm_benchmark <- function(size = 10){
  A <- matrix(runif(size * size), size, size)
  B <- matrix(runif(size * size), size, size)

  tic <- Sys.time()
  C <- A %*% B
  toc <- Sys.time()
  cat(sprintf("built_in MM \t %.4f sec\n", toc - tic));

  tic <- Sys.time()
  C <- DGEMM(A, B)
  toc <- Sys.time()
  cat(sprintf("openmp dgemm MM \t %.4f sec\n", toc - tic));

  tic <- Sys.time()
  C <- strassenMM(A, B)
  toc <- Sys.time()
  cat(sprintf("strassenMM MM \t %.4f sec\n", toc - tic));

  tic <- Sys.time()
  C <- dgemm_blas(A, B)
  toc <- Sys.time()
  cat(sprintf("BLAS DGEMM MM \t %.4f sec\n", toc - tic));
}


##' function of logistic regression CV
##'
##' @title glmCV
##' @param data
##' @param lambda numeric vector
##' @param fold cross validation fold
##' @return best lambda
##' @examples
##' data(mini_mnist)
##' glmCV(X=mini_mnist$train$images, Y=mini_mnist$train$labels)
##' @export
##' @author xin zhou \url{xxz220@@miami.edu}
glmCV <- function(X, Y, lambda = 10^(seq(-3, 1, by = 0.5)), fold = 5){
  idx <- sample(1:fold, nrow(Y), replace = TRUE)
  cv.lambda <- data.frame()
  for(i in lambda){
    result <- NULL
    for(k in 1:fold){
      LR <- new("logisticRegression", X=X[-which(idx==k),], Y=Y[-which(idx==k),], lambda=i)
      O  <- new("Optimizer", p = LR, w = matrix(0, nrow = ncol(X), ncol =  ncol(Y)), iter = 100)
      O  <- train(O)
      N  <- new("logisticRegression", X=X[which(idx==k),], Y=Y[which(idx==k),], lambda=i)
      result <- c(result, error(N, O))
    }
    cv.lambda <- rbind(c(i, mean(result)))
  }
  cv.lambda
}
