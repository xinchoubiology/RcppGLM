##' default dimension methods
##'
##' @rdname dimension-methods
##' @description dimension method return the dimension of variable X
##'              {n x p | n = #observation, p = #feature, k = #class}
##' @return list
##'         N predictor number for each observation
##'         P feature number in GLM
##'         K class number of observation
##' @exportMethod dimension
setMethod("dimension",
          "GLM",
          function(object){
            if(!all(c("X", "Y") %in% slotNames(object)))
              stop("Observation missing in optimization problem class. ")

            list(N = nrow(object@X), P = ncol(object@X), K = ncol(object@Y))
          })

##' get object function value
##'
##' @rdname objval-methods
##' @description return the objective function value at w
##'
##' @param w p x k coefficient matrix
##' @exportMethod objval
setMethod("objval",
          "GLM",
          function(object, w){
            ## virtual GLM class method
            stop("return the objective function value at w")
          })





