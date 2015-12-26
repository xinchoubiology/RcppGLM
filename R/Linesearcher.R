##' Line searcher function
##' @rdname linesearch
##' @param a m1 in f(xᵢ + t*d) <= f(xᵢ) + m₁*t<∇f(xᵢ) , d>
##' @param b m2 in <∇f(xᵢ + t*d), d> >= m₂<∇f(xᵢ), d>
##' @param t0 init step size
##' @param tol tolerance
##' @description linesearcher method for GLM class
##' @export
wolfe_linesearcher <- function(a = 0.01, b = 0.9, t0 = 1, tol = 0.001, ...){
  function(object, w, d){
    low <- 0; high <- 1e7
    ## init t
    t  <- t0
    fx <- objval(object, w)
    g  <- gradient(object,w)
    dot <- crossprod(c(g), c(d))[1]
    while(TRUE){
      if(high - low < tol)
        break
      if(objval(object, w + t * d) > fx + a * t * dot){
        high <- t
        t <- (low + high) / 2
      }
      else if(crossprod(c(gradient(object,w + t * d)), c(d)) < b * dot){
        low <- t
        t <- (low + high) / 2
      }
      else
        break
    }
    t
  }
}


##' Linesearch backtrack
##' @title backtrack_linesearcher
##' @rdname linesearch
##' @param a f(x + t * Δx) ≦ f(x) + a.t<∇f(x), Δx
##' @param b
##' @description define lineseaher method
##' @export
backtrack_linesearcher <- function(a = 0.4, b = 0.8,...){
  function(object, w, d){
    t <- 1e7
    fx <- objval(object, w)
    g  <- gradient(object,w)

    while(objval(object, w + t * d) > fx + a * t * crossprod(c(g), c(d))[1]){
      t <- b * t
    }
    t
  }
}
