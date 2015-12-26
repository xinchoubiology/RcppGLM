##' @docType methods
##' @name summary
##' @rdname summary-methods
##' @title summary method
##' @param object one of \code{Optimizer} object
##' @return summary object
##' @export
setGeneric("summary", function(object) standardGeneric("summary"))

##' @docType methods
##' @name dimension
##' @rdname dimension-methods
##' @title dimension method
##' @param object one of \code{GLM} object
##' @return dimension
##' @export
setGeneric("dimension", function(object) standardGeneric("dimension"))

##' @docType methods
##' @name objval
##' @rdname objval-methods
##' @title objval method
##' @param object one of \code{logisticRegression} object
##' @return objval object
##' @export
setGeneric("objval", function(object, w) standardGeneric("objval"))

##' @docType methods
##' @name gradient
##' @rdname gradient-methods
##' @title gradient method
##' @param object one of \code{logisticRegression} object
##' @return summary object
##' @export
setGeneric("gradient", function(object, w) standardGeneric("gradient"))

##' @docType methods
##' @name solve_hessian
##' @rdname solve_hessian-methods
##' @title solve_hessian method
##' @param object one of \code{logisticRegression} object
##' @return solve_hessian object
##' @export
setGeneric("solve_hessian", function(object, w, g) standardGeneric("solve_hessian"))

##' @docType methods
##' @name train
##' @rdname train-methods
##' @title train method
##' @param object one of \code{Optimizer} object
##' @return train object
##' @export
setGeneric("train", function(object, verbose = TRUE) standardGeneric("train"))

##' @docType methods
##' @name predict
##' @rdname predict-methods
##' @title predict method
##' @param object one of \code{GLM}, \code{logisticRegression} object
##' @return predict object
##' @export
setGeneric("predict", function(object, model) standardGeneric("predict"))

##' @docType methods
##' @name error
##' @rdname error-methods
##' @title error method
##' @param object one of \code{GLM} object
##' @return error object
##' @export
setGeneric("error", function(object, model) standardGeneric("error"))
