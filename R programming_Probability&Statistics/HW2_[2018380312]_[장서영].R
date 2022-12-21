##################################
## Assignment 21                ##
## for Probability & Statistics ##
## Seoyoung Jang                ##
## 2022-11-29                   ##
##################################

## Initial Settings
setRepositories(ind = 1:7)

install.packages("data.table")
library(data.table)

setwd("C:\\Users\\jangs\\Rprojects")
getwd()

data <- data.frame(fread("Data.txt", sep = "\t", head=T, stringsAsFactors = T))

Age <- data$Age
Height <- data$Height_CM
Weight <- data$Weight_KG
SysBP <- data$sysBP
HR <- data$HR
Resting <- data$Resting_SaO2
BMI <- data$BMI
FEV1 <- data$FEV1
FVC <- data$FVC
Disease <- data$Disease


## Q1
Gender <- data$Gender

Data <- data.frame(Age, Gender) 
t.test(Age~Gender, Data)

Data <- data.frame(Height, Gender) 
t.test(Height~Gender, Data)

Data <- data.frame(Weight, Gender) 
t.test(Weight~Gender, Data)

Data <- data.frame(SysBP, Gender) 
t.test(SysBP~Gender, Data)

Data <- data.frame(HR, Gender) 
t.test(HR~Gender, Data)

Data <- data.frame(Resting, Gender) 
t.test(Resting~Gender, Data)

Data <- data.frame(BMI, Gender) 
t.test(BMI~Gender, Data)

Data <- data.frame(FEV1, Gender) 
t.test(FEV1~Gender, Data)

Data <- data.frame(FVC, Gender) 
t.test(FVC~Gender, Data)


## Q2
Race <- factor(c(rep("1", 30), rep("2", 30)))
Height <- c(rnorm(30, 173, 2), rnorm(30, 173, 2))

Data <- data.frame(Height, Race)

obs_t_stat <- as.numeric(t.test(Height ~ Race, Data)$statistic)

null_t_stat <- c()
numOfRepeat <- 1000

for(i in 1:numOfRepeat){
  null_t_stat[i] <- as.numeric(t.test(Height ~ sample(Race), Data)$statistic)
}

null_t_stat <- sort(null_t_stat)
print(null_t_stat)


## Q3
Gender <- rep("Female", 100)
Height <- c(rnorm(100, 162.7, 40))

Data <- data.frame(Height, Gender)

t.test(Height~Gender, Data, alternative = "two.sided")$p.value 
t.test(Height~Gender, Data, alternative = "less")$p.value 
t.test(Height~Gender, Data, alternative = "greater")$p.value 


## Q4
Disease <- factor(c(rep("COVID-19", 100), rep("Healthy", 100)))

# P-value in White/black American
Race <- factor(c(rep("1", 100), rep("2", 100)))

Data1 <- data.frame(Disease, Race[1])
Data2 <- data.frame(Disease, Race[2])

obs_t_stat <- as.numeric(t.test(Disease ~ Race, Data)$statistic)

null_t_stat1 <- c1()
null_t_stat2 <- c2()

numOfRepeat <- 1000

for(i in 1:numOfRepeat){
  null_t_stat1[i] <- as.numeric(t.test(Height ~ sample(Race), Data)$statistic)
}
for(i in 1:numOfRepeat){
  null_t_stat2[i] <- as.numeric(t.test(Height ~ sample(Race), Data)$statistic)
}

Pval <- (sum(abs(null_t_stat) >= abs(obs_t_stat)) + 1) / numOfRepeat
Pval

P


