##################################
## Lecture Material             ##
## for Probability & Statistics ##
## Minseok Seo                  ##
## 2022-09-21                   ##
##################################

setRepositories(ind = 1:7)

install.packages("devtools")
library(devtools)

install_github('jhk0530/Rstat')
install.packages("ggVennDiagram")
install.packages("animation")

library(Rstat)
library(ggVennDiagram)
library(animation)
library(dplyr)


## Set two fair dice (Self-Checking 1)
nsides <- 6
times <- 2

temp <- list()

for (i in 1:times) {
  temp[[i]] <- 1:nsides
}

## Sample Space S
S <- expand.grid(temp, KEEP.OUT.ATTRS = FALSE)
names(S) <- c(paste(rep("Dice_", times), 1:times, sep = ""))
nrow(S)



## For combination
S

for(i in 1:nrow(S)){
  S[i,] <- sort(as.numeric(S[i,]))
}

distinct(S)
S <- distinct(S)
nrow(S)

## Get Event A
eventA <- subset(S, ((Dice_1+Dice_2) %% 2)==0)
element(eventA)

## Get Event B
eventB <- subset(S, (Dice_1+Dice_2) >=8)
element(eventB)

## Get Event C
eventC <- subset(S, abs(Dice_1 - Dice_2) <= 1)
element(eventC)

## Intersection
AB <- intersect2(eventA, eventB)
AC <- intersect2(eventA, eventC)
BC <- intersect2(eventB, eventC)

## Complement
Ac <- setdiff(S, eventA)
Bc <- setdiff(S, eventB)
Cc <- setdiff(S, eventC)

## Drawing Venn-diagram
vennData <- list(A = element(eventA),
                 B = element(eventB),
                 C = element(eventC))

ggVennDiagram(vennData)



## Simulation of law of large numbers (Self-Checking 2)
ani.options(nmax = 1000, interval = 0.00001)
win.graph(7,4)

lln.ani(FUN = function(n, mu) rbinom(n, size=1, prob = mu), mu = 0.5, type="n", col.poly="blue")

title(main = "Law of Large Numbers (Korea Univ.)")




## Self-Checking non-amination version
nTimes <- 100

eventCoin <- c()

for(i in 1:nTimes){
  eventCoin[i] <- rbinom(1, size=1, prob = 0.5)
  print(paste0(i, " times drawing... Prob(Head) = ", (sum(eventCoin == 1) / length(eventCoin))))
}






