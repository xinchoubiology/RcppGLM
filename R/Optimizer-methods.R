##' constructor for Optimizer
##'
##' @rdname initialize-methods
##' @param p optimization problem class
##' @param w0 initialization coefficient matrix
##' @param direction character c("gradient", "newton", "stochastic gradient")
##' @param stepsize character c("wolfe", "backtrack")
##' @param maxiter maximum iteration; default = 100
##' @param wtol coefficient criteria for stop iteration
##' @param gtol gradient tolerance
##' @param ftol function value tolerance
##' @exportMethod initialize
##' @examples
##' data(mini_mnist)
##' LR <- new("logisticRegression", X=mini_mnist$train$images, Y=mini_mnist$train$labels, lambda=0.5)
##' O  <- new("Optimizer", p = LR, w = matrix(0, nrow = 784, ncol = 10), iter = 1000)
setMethod("initialize",
          "Optimizer",
          function(.Object,
                   p,
                   w = NULL,
                   direction = c("gradient", "newton", "stochastic gradient"),
                   stepsize = c("wolfe", "backtrack"),
                   wtol = 1e-7, gtol = 1e-7,
                   ftol = 1e-7, iter = 100, t = 1.0, ...){

            if(! direction %in% c("gradient", "newton", "stochastic gradient") ||
               ! stepsize %in% c("wolfe", "backtrack"))
              stop("Error candidate value match for direction and stepsize. ")

            .Object@p <- p
             DIM <- dimension(.Object@p)
            .Object@w      <- w
            .Object@w_prev <- matrix(0, nrow = DIM$P, ncol = DIM$K)      ## coefficient
            .Object@g      <- gradient(.Object@p, w)                     ## gradient
            .Object@g_prev <- matrix(0, nrow = DIM$P, ncol = DIM$K)
            .Object@f      <- objval(.Object@p, w)                       ## function value
            .Object@f_prev <- 0.0
            .Object@direction <- match.arg(direction)
            .Object@stepsize  <- match.arg(stepsize)
            .Object@wtol <- wtol
            .Object@gtol <- gtol
            .Object@ftol <- ftol
            .Object@maxiter <- iter
            .Object@iter <- 1
            .Object@d    <- matrix(0, nrow = DIM$P, ncol = DIM$K)
            .Object@t    <- t
            .Object
          })

##' Optimizer train
##'
##' @rdname train-methods
##' @param verbose display iteration information; default TRUE
##' @exportMethod train
setMethod("train",
          "Optimizer",
          function(object, verbose = TRUE){

            calcdir <- function(){}
            ## define differential direction in coefficient update
            if(object@direction == "gradient"){
              calcdir <- function(){
                object@d <<- object@g
              }
            }
            else{
              calcdir <- function(){
                object@d <<- solve_hessian(object@p, w = object@w, g = object@g)
              }
            }
            ## define stepsize
            get_linesearcher <- function(stepsize){
              if(stepsize == "wolfe"){
                wolfe_linesearcher()
              }
              else{
                backtrack_linesearcher()
              }
            }
            ## setMethods linesearch
            linesearcher    <- get_linesearcher(object@stepsize)
            object@iter     <- 1
            while(object@iter < object@maxiter){
              object@iter   <- object@iter + 1
              object@w_prev <- object@w
              object@g_prev <- object@g
              object@f_prev <- object@f
              object@g      <- gradient(object@p, object@w_prev)
              ## object@d direction
              calcdir()
              object@t      <- linesearcher(object@p, object@w_prev, object@d)
              cat(sprintf("stepsize is (%f): \t", object@t))
              object@w      <- object@w_prev -  object@d
              object@f      <- objval(object@p, object@w)

              if(verbose){
                cat(sprintf("%d: %4f (%f)\n", object@iter, object@f, object@f - object@f_prev))
              }
              ## stop criteria
              if(abs(object@f - object@f_prev) <= object@ftol)
                break;
              if(norm(object@w - object@w_prev, "2") <= object@wtol)
                break;
              if(object@iter > 2){
                if(norm(object@g, "2") <= object@gtol)
                  break;
              }
            }
            return(object)
          })





