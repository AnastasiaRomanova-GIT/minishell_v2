# Fixing of agreements for further references + resourses
## Contents
[Switching between branches](#how-to-effectively-switch-between-branches-in-git)  
[Resourses](#resourses)

I would suggest we use some file-locks: once a file is in the work of one, mark it... may be in the name

## how to effectively switch between branches in git

**Note** Pushing and merging to main could be different. Not super sure about the potential issues at the moment.

**0.** From inside the personal branch, merge the latest changes. We hope to minimize the amout of git-conflicts to solve
```
git merge test
```
**1.** Do the changes and save them.
**2.** Add and commit the changes (as usuall).
```te
git add [files / .]
git commit [-m "commit message" / editor of the choise"]
```
**3.** Switch to the test branch by 
```
git switch test
```
**4.** Add the last commits to the test by 
```
git merge [Ana/Rana]
```
There is no need to make yet another commit in the test branch

Pushing to personal branches would require setting the branch as upstream. Generally, git dii not allow me pushing to an upstream branch from non-active lacking branch. It also shows the right command to use to change the upstream. With the trials from today it seems pretty intuitive, so I would suggest to hope it will be intuitive further on.

## Resourses
* [creating a minishell within 10 mins](https://youtube.com/watch?v=k6TTj4C0LF0&si=yGn2u-6tZUfh11W1)

* [youtube list with seemingly cool explanations](https://www.youtube.com/watch?v=cIBmeEpsMj0&list=PLxIRFba3rzLzxxZMMbrm_-mkI7mV9G0pj)

* Great channel with short videos which pin point some concepts. [This video is on fsanitize](https://www.youtube.com/watch?v=tEbV21aPSKw&t=80s)

* [List of videos](https://www.youtube.com/playlist?list=PLK4FY1IoDcHG-jUt93Cl7n7XLQDZ0q7Tv) on forks and pipes 
