##################################
## Assignment 1                 ##
## for Probability & Statistics ##
## Seoyoung Jang                ##
## 2022-11-15                   ##
##################################

## Initial Settings
setRepositories(ind = 1:7)

install.packages("data.table")
library(data.table)

setwd("C:\\Users\\jangs\\Rprojects")
getwd()

data <- data.frame(fread("Data.txt", sep = "\t", head=T, stringsAsFactors = T))



covid19 <- subset(data, data["Disease"] == "COVID19")

x_bar <- mean(covid19$sysBP)
n <- nrow(covid19)
mu <- 128.65
var <- 16.5^2

z.test <- function(input, mu, var){
  z <- (mean(input) - mu) / (sqrt(var / length(input)))
  return(z)
}

Zstat <- z.test(covid19$sysBP, mu, var) 
                
## Q1.
2*pnorm(-abs(Zstat))

## Q2.
1-pnorm(Zstat)


## Q3.
HR_covid19 <- subset(data, subset = (data["Disease"] == "COVID19" & data["Gender"] == 1))
x_bar <- mean(HR_covid19$HR)
n <- nrow(HR_covid19)
mu <- 74.62
var <- sqrt(11.1)

Zstat <- z.test(HR_covid19$HR, mu, var) 

# 1.
2*pnorm(-abs(Zstat))
# 2.
1-pnorm(Zstat)   
# 3.
pnorm(Zstat)

## Q4.
## 답안 파일에 작성함


