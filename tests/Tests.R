
gen_data <- function() {
	n1 <- sample(1:10,1)
	n2 <- sample(1:10,1)
	x1 <- rnorm(n1)
	x2 <- rnorm(n2)
	tryCatch({
		test <- ks.test(x1,x2)
		st <- test$statistic
		p <- test$p.value
		cat(n1, n2, x1, x2, st, p, "\n")
	}, error = function(e) {})
}

sink("TestingData.txt")
for (i in 1:100) gen_data()
sink()

