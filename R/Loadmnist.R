##' Load MNIST digit recognition database(.Rda) into R environment
##'
##' @title loadMNIST
##' @param verbose bool; Default TRUE
##' @return List
##'         train
##'         test
##' @export
##' @author xin zhou \url{xxz220@@miami.edu}
loadMNIST <- function(verbose = TRUE){
  if(verbose){
    cat(sprintf("Loading data ..."))
  }
  data(mini_mnist)
  mnist <- list(train = mini_mnist$train, test = mini_mnist$test)
  mnist
}


##' label_mnist : transform Y(n x K) to digits label
##'
##' @title labelMNIST
##' @param Y output matrix
##' @return label of digits, from 0 to 9
##' @export
##' @author xin zhou \url{xxz220@@miami.edu}
labelMNIST <- function(Y){
  apply(Y, 1, function(x){which(x == 1) - 1})
}

##' mnist_show
##'
##' @title mnist_show
##' @param img mnist image matrix
##' @param grid picture pixel resolution
##' @param ncol digit number each row
##' @description plot logistic regression training set
##' @import ggplot2 reshape gridExtra
##' @export
##' @examples
##' imag <- loadMNIST()
##' train <- imag$train$images[(1:100), ]
##' mnist_show(train)
##' @author xin zhou \url{xxz220@@miami.edu}
mnist_show <- function(img, grid = 28, ncol = 10, plot = TRUE, label){
  nimg <- dim(img)[1]
  pltlist <- lapply(1:nimg, function(i){
                              iimg <- melt(matrix(img[i,], nrow = grid)[,(grid:1)])
                              p <- ggplot(iimg, aes(x = X1, y = X2, fill = value)) + geom_tile() +
                                   scale_fill_gradient2(low = "white", high = "black", midpoint = 0) +
                                   ggtitle(as.character(label[i]))
                              p <- p + theme_bw() + theme(title = element_text(colour = "blue",
                                                                          size = 10,
                                                                          face = "bold"),
                                                          line = element_blank(),
                                                          panel.border = element_blank(),
                                                          axis.title = element_blank(),
                                                          axis.ticks = element_blank(),
                                                          axis.text  = element_blank(),
                                                          legend.position = "none")

                              p
                         })
  if(plot){
    pdf(file = "mnist.pdf", width = 7, height = 1 * length(label) / ncol)
    multiplot(pltlist, ncol = ncol)
    dev.off()
  }
  pltlist
}

##' multiplot
##'
##' ggplot objects
multiplot <- function(plotlist = NULL, ncol = 1, layout = NULL){
  numplots <- length(plotlist)
  if(is.null(layout)){
    layout <- matrix(seq(1, ncol * ceiling(numplots / ncol)),
                     ncol = ncol,
                     nrow = ceiling(numplots / ncol))
  }
  if(numplots == 1){
    print(plotlist[[1]])
  } else{
    grid.newpage()
    pushViewport(viewport(layout = grid.layout(nrow = nrow(layout), ncol = ncol(layout))))

    for(i in 1 : numplots){
      matchIdx <- as.data.frame(which(layout == i, arr.ind = TRUE))
      print(plotlist[[i]], vp = viewport(layout.pos.row = matchIdx$row,
                                         layout.pos.col = matchIdx$col))
    }
  }
}




