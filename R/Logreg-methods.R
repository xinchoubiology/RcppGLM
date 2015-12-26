##' get object function value
##'
##' @rdname objval-methods
##' @description return the objective function value at w.
##'              w0
##'
##' @param w p x k coefficient matrix
##' @return log liklihood
##' @importFrom psych tr
##' @exportMethod objval
setMethod("objval",
          "logisticRegression",
          function(object, w){
            loglik <- loglikelihood(object@Y, object@X, w)
            return(-loglik)
          })

##' gradient of logistic regression
##'
##' @rdname gradient-methods
##' @description return gradient of logistic regression model
##' @param w coefficient in Xw
##' @return gradient matrix
##' @exportMethod gradient
setMethod("gradient",
          "logisticRegression",
          function(object, w){
            m <- nrow(object@X)
            -1 * crossprod(object@X, object@Y - condprob(object@X, w)) + object@lambda * w / m
          })

##' solve Hessian matrix
##' @rdname solve_hessian-methods
##' @description return solved direction of newton rasphon (H^{-1}g)
##' @param w coefficient in Xw
##' @param g gradient of matrix
##' @exportMethod solve_hessian
setMethod("solve_hessian",
          "logisticRegression",
          function(object, w, g){
            J <- ncol(w)
            Hess <- hessian(object@X, w, object@lambda)
            d <- lapply(1:J,
                        function(i){
                          solve(Hess[[i]]) %*% g[,i,drop=FALSE]
                        })
            return(do.call(cbind, d))
          }
         )

##' predict category
##' @rdname predict-methods
##' @description predict categorical of each observation
##' @param object input observation matrix
##' @param model optimizer model
##' @exportMethod predict
setMethod("predict",
          "logisticRegression",
          function(object, model){
            category <- condprob(object@X, model@w)
            max <- apply(category, 1, max)
            (category == max) * 1
          }
         )

##' error calculation
setMethod("error",
          "logisticRegression",
          function(object, model){
            pred <- predict(object, model)
            y    <- object@Y
            sum(abs(pred - y)/2) / nrow(Y)
          })

##' loglikelihood to calculate the objval for logistic regression
loglikelihood <- function(y, X, w){
  options(warn = -1)
  ## check x (N x p) w (p x K) =  y (N x K)
  if(dim(X)[1] != dim(y)[1] || dim(X)[2] != dim(w)[1] || dim(y)[2] != dim(w)[2])
    stop("incompatible dimension of predictor matrix and response matrix")

  ## X^T W, each row(J col) is the \sum_{p=1}^p X_{ip}b_{pj} --> N x K matrix
  xw <- X %*% w
  maxw <- apply(xw, 1, max)
  xw <- xw - maxw
  ## Loss function =
  ## \sum_{i=1}^N[\sum_{j=1}^{J-1} \mathbf{Y}_{ij}\sum_{k=1}^pX_{ik}\beta_{kj}
  ## - n_i(\log[1+\sum_{j=1}^{J-1}e^{\sum_{k=1}^pX_{ik}\beta_{kj}}]]
  sum(diag(tcrossprod(y, xw)) - log(rowSums(exp(xw))))
}

##' conditional probability for gradient descent
condprob <- function(X, w){
  w <- as.matrix(w)
  xw <- X %*% w
  if(dim(w)[2] == 1){
    c(1 / (1 + exp(-xw)))
  }
  else{
    xw <- xw - xw[, dim(xw)[2]]
    maxw <- apply(xw, 1, max)
    exp(xw - maxw) / rowSums(exp(xw - maxw))
  }
}

##' hessian matrix
hessian <- function(X, w, lambda){
  probs <- condprob(X, w)
  dims  <- nrow(w) * ncol(w)
  Hess  <- list()
  if(ncol(w) == 1){
    ## t(X)DX and D is \pi_i\pi_j and \pi_i(1-\pi_i) on diagonal
    ## D is a n x n matrix
    D <- diag(probs) - tcrossprod(probs)
    Hess[[1]] <- crossprod(X, D %*% X) + diag(lambda / dims, dims)
  }
  else{
    ## if we have J class, we will have J hessian for each column of w
    Hess <- lapply(1:ncol(w),
                   function(j){
                     crossprod(X, diag(probs[,j] * (1 - probs[,j])) %*% X) + lambda * diag(1 / nrow(w), nrow(w))
                   })
  }
  Hess
}



