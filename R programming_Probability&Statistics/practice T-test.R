## Initial Settings
setRepositories(ind = 1:7)

install.packages("data.table")
library(data.table)

setwd("C:\\Users\\jangs\\Rprojects")
getwd()

Data20 <- data.frame(fread("Data1_PS_2020.txt", sep = "\t", head=T, stringsAsFactors = T))
Data21 <- data.frame(fread("Data1_PS_2021.txt", sep = "\t", head=T, stringsAsFactors = T))
Data22 <- data.frame(fread("Data1_PS_2022.txt", sep = "\t", head=T, stringsAsFactors = T))

## Q1.

# str(Data20)
# str(Data21)
# str(Data22)

HW1_20 <- Data20$HW1
Hw2_20 <- Data20$HW2
HW3_20 <- Data20$HW3
T_20 <- Data20$Total

HW1_21 <- Data21$HW1
Hw2_21 <- Data21$HW2
HW3_21 <- Data21$HW3
T_21 <- Data21$Total

HW1_22 <- Data22$HW1
Hw2_22 <- Data22$HW2
HW3_22 <- Data22$HW3
T_22 <- Data22$Total

# mean(HW1_20)
# mean(HW1_21)
# mean(HW1_22)

# HW1
t.test(HW1_20, HW1_21)$p.value
t.test(HW1_21, HW1_22)$p.value
t.test(HW1_20, HW1_22)$p.value

# HW2
t.test(HW2_20, HW2_21)$p.value
t.test(HW2_21, HW2_22)$p.value
t.test(HW2_20, HW2_22)$p.value

# HW3
t.test(HW3_20, HW3_21)$p.value
t.test(HW3_21, HW3_22)$p.value
t.test(HW3_20, HW3_22)$p.value

# Total
t.test(T_20, T_21)$p.value
t.test(T_21, T_22)$p.value
t.test(T_20, T_22)$p.value


## Q2.
#HW1
HW1 <- c(HW1_20, HW1_21, HW1_22)
year <- c(rep("2020", length(HW1_20)), rep("2021", length(HW1_21)), rep("2022", length(HW1_22)))

boxplot(HW1 ~ year, data = data.frame(HW1, year), ylab = "HW1 Score")

#HW2
HW2 <- c(HW2_20, HW2_21, HW2_22)
year <- c(rep("2020", length(HW2_20)), rep("2021", length(HW2_21)), rep("2022", length(HW2_22)))

boxplot(HW2 ~ year, data = data.frame(HW2, year), ylab = "HW2 Score")

#HW3
HW3 <- c(HW3_20, HW3_21, HW3_22)
year <- c(rep("2020", length(HW3_20)), rep("2021", length(HW3_21)), rep("2022", length(HW3_22)))

boxplot(HW3 ~ year, data = data.frame(HW3, year), ylab = "HW3 Score")

#Total
Total <- c(T_20, T_21, T_22)
year <- c(rep("2020", length(T_20)), rep("2021", length(T_21)), rep("2022", length(T_22)))

boxplot(Total ~ year, data = data.frame(Total, year), ylab = "Total Score")



#####################################

Data2 <- data.frame(fread("Data2.txt", sep = "\t", head=T, stringsAsFactors = T))

## Q6.
Gender <- Data2$Gender

t.test(numTardy~Gender, Data2, alternative = "two.sided")$p.value 
# t.test(numTardy~Gender, Data2, alternative = "less")$p.value 
# t.test(numTardy~Gender, Data2, alternative = "greater")$p.value 

# t.test(numTardy~Gender, Data2, alternative = "two.sided")
t.test(numTardy~Gender, Data2, alternative = "less")
t.test(numTardy~Gender, Data2, alternative = "greater")


## Q7.
wilcox.test(numTardy~Gender, Data2, exact = FALSE)$p.value 


## Q8.
Gender <- Data2$Gender

t.test(numTardy~Gender, Data2, alternative = "two.sided")$p.value 
t.test(numTardy~Gender, Data2, alternative = "less")$p.value 
t.test(numTardy~Gender, Data2, alternative = "greater")$p.value 






