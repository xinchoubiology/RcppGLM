##' __cplusplus__ class nested && S4 object nested
##'
##' Class "GLM"
##' @name GLM-class
##' @description GLM-class is a virtual Class. Inherited by C++ backend object or S4 object
##' @slot lambda L2 regulizer parameter
##' @keywords classes
##' @exportClass GLM
##' @author xin zhou \url{xxz220@@miami.edu}
setClass(Class = "GLM",
         representation(
           lambda = "numeric",
           "VIRTUAL")
         )

##' optimization related function
##' Class logisticRegression
##' @name logisticRegression-class
##' @aliases logisticRegression-class
##' @docType class
##' @slot X x values (bias term added) [1, x]
##' @slot Y y values Matrix
##' @slot w coefficient values
##' @slot lambda parameter for regularization
##' @seealso \code{\link{logisticRegression}}
##' @keywords classes
##' @exportClass logisticRegression
##' @author Zhou Xin
setClass(Class = "logisticRegression",
         representation(
           X = "matrix",
           Y = "matrix"
         ),
         contains = c("GLM")
         )


##' Class "Optimizer"
##'
##' @name Optimizer-class
##' @docType class
##' @slot p \code{GLM} object
##' @slot w coefficient matrix
##' @slot w_prev coefficient matrix of last iteration
##' @slot g gradient matrix
##' @slot g_prev gradient matrix of last iteration
##' @slot f objective function value
##' @slot f_prev objective function value of last iteration
##' @slot d direction coefficient matrix
##' @slot direction direction methods; character c("gradient", "newton", "stochastic gradient")
##' @slot stepsize stepsize methods; character c("wolfe", "backtrack")
##' @slot maxiter maximum iteration; default = 100
##' @slot iter iteration number
##' @slot wtol coefficient criteria for stop iteration
##' @slot gtol gradient tolerance
##' @slot ftol function value tolerance
##' @slot t stepsize
##' @keywords classes
##' @exportClass Optimizer
##' @author xin zhou \url{xxz220@@miami.edu}
setClass(Class = "Optimizer",
            representation(
              p = "GLM",
              w = "matrix",
              w_prev = "matrix",
              g = "matrix",
              g_prev = "matrix",
              f = "numeric",
              f_prev = "numeric",
              d = "matrix",
              direction = "character",
              stepsize = "character",
              maxiter = "numeric",
              iter = "numeric",
              wtol = "numeric",
              gtol = "numeric",
              ftol = "numeric",
              t    = "numeric"
            )
         )

