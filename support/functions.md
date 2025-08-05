# Docs for functions and particularities

## Content
[usefull links](#usefull-links)  
[How To's](#how-tos)
## How To's
### how to effectively switch between branches in git

**Note** Pushing and merging to main could be different. Not super sure about the potential issues at the moment.

**0.** From inside the personal branch, merge the latest changes. We hope to minimize the amout of git-conflicts to solve
```
git merge test
```
**1.** Do the changes and save them.
**2.** Add and commit the changes (as usuall).
```
git add [files / .]
git commit [-m "commit message" / editor of the choise"]
```
**3.** Switch to the test branch by 
```
git switch test
```
**4.** Add the latest commits to the test by 
```
git merge [Ana/Rana]
```
There is no need to make yet another commit in the test branch

Pushing to personal branches would require setting the branch as upstream. Generally, git dii not allow me pushing to an upstream branch from non-active lacking branch. It also shows the right command to use to change the upstream. With the trials from today it seems pretty intuitive, so I would suggest to hope it will be intuitive further on.

## Usefull links
[Gantt charts to implement in git](https://github.com/realm/github-gantt)
