---
layout: default
title: Version Control
nav_order: 3
---

# Version Control

Modifying WoTLK is often a very delicate process, where the tiniest mistake can start causing bugs in completely unrelated places and in very unexpected ways.

Being able to efficiently create backups of your project is **one of the most important skills** you can learn, and one of the most powerful problem solving techniques you can apply.

_This tutorial is meant as a general introduction to version control for those unfamiliar with it. If you're already highly proficient in git, there won't be much new here._

## 'Save often and make backups'

The simplest form of version control is simply to save your work often and to create copies of the files that you edit.

While it's far from the best technique available, it's one that many projects rely on since it requires next to no technical proficency.

Some things to keep in mind if this is the approach you choose:

- Be careful with how you copy SQL databases and don't naively copy the database files on the filesystem, since these may be actively written to while you copy them and cause corruption. Prefer 'dumping' your world database properly to an SQL file using an editor like [HeidiSQL](https://www.heidisql.com/).

- Be aware that some editors edit files other than the one you have currently opened yourself. Without a proper version control system installed, you won't have any reliable way to tell what files have actually changed.

## Git

Git is the most popular method of version-control for text files by far, and is used by virtually every wow emulator and tool. However, with some work it is also very possible to use git for binary files, and can be extremely powerful for creating incremental backups as you're attempting a new kind of difficult edit or mod.

### Learning Git

Git is a relatively simple tool for most uses, but has a learning curve that spikes early on and isn't something you should expect to understand intuitively right away. Depending on your previous experience, this may be between a couple of hours and a couple of days actively spending time with it to understand what git is and what it does.

There are a lot of different tutorials and guides for learning the basics of git, and we will only list a few of them here:

- [Oh My Git!](https://ohmygit.org/) - An educational game that teaches the basic concepts of git.

- [Learn Git Branching](https://learngitbranching.js.org/) - An interactive tutorial that shows both git commands and a visual representation of the version tree as you work on it.

- [Codeacademy](https://www.codecademy.com/courses/learn-git/lessons/git-workflow/exercises/git-init) - A free step-by-step interactive course that works directly with git commands.

### GUI vs Command-line

You can work with git both using GUI tools and the command-line. Which one is more hardcore and which one should you use?

One benefit of learning the git command-line is that you get a universal language for 'understanding' git. GUIs often have different names, buttons and layouts that can make it hard to find tutorials and to discuss with other developers.

However, just sticking to using git on the command-line isn't necessarily the best option either. One of the greatest benefits of GUI tools is the ability to **visualize** your version tree, quickly see what branch you are currently on and how it differs from other branches.

I personally think that an optimal way of using git is to:

- Learn it on the command line
- Use it with a GUI tool

## Version Control for Problem Solving

The rest of this guide will use `git` as a tool for various problem-solving techniques that commonly come up in WoW modding. It will assume that you have a solid grasp on git fundamentals from the above tutorials, and master concepts like `commits`, `branches`, `merges`, `reverts` and `squashing`.

### About commit names

Many people who work with git are nervous about when to make a commit and not, feeling that commits should introduce a 'sensible feature' and be highly thought out.

While this is, generally, true when working with git against an open source repository, this does **not apply** when using it as a problem-solving tool locally. For wow modding, we are going to need **a lot** more commits than what is sensible in a public repository.

Commit names, at this stage, should only describe the bare minimum of the changes we've applied to our system. Later, once we're confident we've accomplished to add a proper feature, we can use `git squash` for a commit we could actually publish somewhere.

Knowing how much to squash and how much to keep is a skill that you learn over time, but it is important to remember that there is **never** any excuse to _not_ make a local commit.

### Adding Features

Let's say we're going to follow a (fictional) tutorial to add a new set of commands that allows players to select more than 2 talent specs on our server. We'll assume that the reader is unfamiliar with this process and doesn't understand much of what these changes actually do.

The tutorial has the following (fictional) steps:

1. add an almost empty script file called `my_script.cpp` to your core
2. "register" this script file in another file called `custom_scripts.cpp`
3. fill out the empty script file with a "command handler" accepts commands but doesn't do anything.
4. apply a "patch" to our core that will change how talent specs are represented
5. add a more advanced snippet to our script file that will tie it to the core path we just applied.
6. Re-compile the core.

Let's say now that we follow all these steps, and on the final step the compiler blows up with errors. What now?

- If we hadn't used version control at all, we might actually struggle to even restore our system to the previous working state. This can be catastrophic.

- If we had used version control, but mixed together this change with another one done right before it, we may be forced to undo both to get the server back into a working state. This can waste a lot of time.

- If we had only worked off a single starting commit and never made any incremental steps, our only option is to attempt the whole thing from the start

- If we had created new temporary commits for every single step we took, we might actually have a suspicion on where we had gone wrong and could start over from there. If we're lucky, we might even be able to try compiling the core in these earlier states to see if the error is still there, or if it changes.
    - _Important: new errors that come up when following a tutorial halfway through may be due to the system not working without all the pieces in place, but may still tell you something important if the error messages change._

### Hunting Regressions

Let's imagine another scenario. You've been running a custom server for a few months, adding tons of patches to it that mostly seem to have worked fine as you added them.

One day, you get a report from a player that your server has a duplication exploit. You gather the details and successfully reproduce it on your local test server. The dupe is not something that seems obviously related to any of the patches you could remember adding, however, as you try the same exploit out on the clean emulator you forked from, the exploit is not possible.

What now?

- If we had not used version control, it's goodbye to every single patch we had added if we want any hope of figuring out what caused this problem, then painstakingly re-applying every single one of them.

- If we had used version control for each of the patches we had applied, it's time to [bisect](https://dev.to/jankoritak/hunting-down-regression-using-git-bisect-4a3l) until we find the patch causing the issue. We can then choose to remove this patch from our server, or get a much narrower view on what might be going wrong to cause it.

### Feature Branching

Sometimes, we find ourselves developing multiple features in our server at the same time. We might be multiple developers working on a single project, or we might just enjoy switching things up every now and then.

[Feature branching](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow) is a workflow all about working individual features to completion in separate git branches until we try to merge them to completion. For projects as complex as custom wow servers, this is an invaluable tool to keep our commit trees clean and easy for the types of problem solving desribed above. Separating half-finished projects until completion is important for a few reasons:

- It stops completely unrelated code from cropping up and breaking our project when we hunt regressions.

- Reverting merge commits is much easier to remove a broken feature than to find all the commits related to it and undoing each of them individually.

- Most serious alternatives to feature branching rely on heavily tested code and continuous integration, which is often very hard to do in wow modding with the poor support for automated testing and deployment.

That doesn't mean there aren't some drawbacks with this approach:

- Features that depend on each others become hard to update in different branches.
- Features that are never tested together can become hard to reconcile both technically and gameplay-wise
- Spawning subprojects can easily become a form of procrastination, as projects have a tendency to be more 'fun' to work on early on early in development.

### Binary Files

One drawback of the amount of changes git can track is working with large binary files. These files are often orders of magnitude larger than the text files git normally works with, and filling your commit tree with binary files can rapidly increase its size. What makes Git so bad at handling large binary files is that you can't really remove things from git history without thoroughly rewriting it, invalidating all commit hashes after the point of history that you want to rewrite. This has two adverse effects:

- Big files take a very long time for developers to clone
- Large repositories will very quickly run into limitations and quotas on servers like GitHub

### Git LFS

[git lfs](https://git-lfs.com/) is a program that allows you to decouple certain files or file formats from your git history itself, instead storing only 'pointers' to files inside your actual repository, while your files are stored elsewhere.

- This alleviates the issue of developers having to download enormous binary repositories, as git lfs allows them to only download the files for the commits they actually check out.

- This does not fix the issue of huge repository sizes on the server, and services like GitHub only offers 1GB in free LFS storage per LFS account.

#### Self-hosted Storage

GitHubs storage quotas are infamously expensive, charging $5 per 50GB of storage/bandwidth. One alternative is to host your own git servers with applications like [Gitea](https://gitea.io/en-us/), [GitLab](https://about.gitlab.com/install/), or to configure git itself to use a separate server for LFS specifically _(todo: write a guide for this)_.

#### Perforce

I honestly do not know anything about perforce but people say you can use it for very good very version control with binary files. It costs money and I'm to stupid to use it so I have no idea, but I'll at least mention it.

#### Local-only Version Control

One alternative is to not use git to track binary files on your server, but instead use things like SQL backups and any separate backup program for other binary files.

At the same time, we could still use git for things like "adding new features" and experimenting, keeping our binary files in a repository specifically for them. A good place for this could be the `patch-4.MPQ` folder we set up earlier.