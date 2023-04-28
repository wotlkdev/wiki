# Problem Solving

It is often said that programming and modding is a practice of "problem-solving", but it is rarely elaborated and effectively isn't saying much more than "just try harder".

Still, modding is unquestionably an often difficult process that tends to go wrong for a variety of reasons, and being able to handle such situations is what will separate a good modder from a decent one.

It is my belief that problem solving is not something reserved only for the "pros", but something you as a beginner can and should practice from your first day of modding, because it is one of the most important skills you can learn from it.

The purpose of this article is to attempt to formulate what I think problem solving is, what strategies I employ to solve problems in WoW modding and what you need to know to do that effectively.

## Computer Skills

Being able to navigate a computer effectively is an important foundation for anything to do with modding. You will be dealing with relatively complex directory hierarchies, edit a lot of text configuration files and have to manage and interface with crappy old GUI or command line programs may or may not do what they are supposed to.

If you are very new to using PCs, are mostly used to working with smartphones or tablets, or have mostly used PCs for gaming or browsing the web, your early struggles with modding will be related to figuring out these basic skills, and it's important to give yourself some time to do that, since many tutorials and guides will assumes those skills.

Remember that, most people who are highly proficient in modding today also had to start clicking random buttons on the screen and trying to figure out what the hell was going on at some point in their lives too.


## Asking Questions

Many people tend to fall on one of two sides of "asking questions about almost everything" or "asking virtually no questions at all". Some people in modding communities become a little weary of people asking many questions and occasionally even looks down on asking questions at all. this isn't good blah blah balh.

### Asking Good Questions

There isn't really a template for asking good questions, but for wow modding there are some general pointers:

- Try to formulate your question completely in a single message.
- If you are following a tutorial, include this and what step you are currently on.
- If your problem consists of an error message, include this.
- If your problem involves feeling confused about a concept, program or guide, mention this.
- If your problem stems from a solution you came up with yourself, **briefly** explain what problem your own solution is meant to solve.

### Bad Question: Direct-messaging helpers

These are questions that you send to people who you may have seen helping other people out in support channels or that you have received help from yourself.

This is a bad way to ask questions, because someone helping you out with something or even many things don't make you friends. Very few helpers appreciate receiving unsolicited direct messages, and the amount of people doing this causes most people actively helping others in support channels to just disable their DMs entirely, making it more difficult for people to reach them for legitimate reasons.

### Bad Question: Asking to ask

These are questions on the form "is this the right forum to ask for xyz?"

Accidentally asking the wrong question in the wrong channel runs only a small risk of being 'wrong' if you read the channel description carefully, but 'asking to ask' **always** wastes everybodys time with an extra notification about nothing.

Nobody appreciates these questions, so don't ask them.

### Bad Question: Soliciting a "helper"

These are questions on the form "can someone help me with <vague problem description>?", or "anybody who is good at <general modding category>?".

This is a bad question, because those answering have no idea about the scope of your question or if they feel like taking the time to answer it. Most people with any experience in forums or messaging apps ignore these questions entirely.

### Bad Question: XY Problem

See [this article.](https://xyproblem.info/)

These are questions that ask about your own solutions rather than the problem you are trying to solve. In wow modding specifically, a similar problem often occurs when asking questions that follow a tutorial without mentioning that tutorial.

These are bad questions, because your own solution might be completely wrong, or the tutorial you are following might be severely outdated.

### Bad Question: Asking to skip work

These are questions on the form "how do i install trinitycore" when they ignore workflows that have clear tutorials for them already.

This is a bad question, because tutorials are there for a reason, and without explaining what about it you need help with or don't understand, most people will assume you're just trying to get someone else to do your own work for you.

Instead, be specific about what you don't understand or why you think the tutorial is too difficult or confusing. Some examples:

- I have tried installing trinitycore through the official tutorial, but I get this error "xyz" when I hit compile and I don't understand what it means.
    - _Why this is good: You clearly specify the step you are stuck on and described the specific problem you've encountered._

- I have tried installing trinitycore, but the tutorial is very overwhelming and I feel like i have no idea what i'm doing. So far I have done "xyz" but I don't know what I'm supposed to do next.
    - _Why this is good: You are honest about being confused about the process and include all the things you think you've done so far._

- I have tried to read the tutorial for installing trinitycore, but it feels like this is too difficult for me to do. Are there any easier tutorials or alternatives to just throw up a small test server for a complete beginner?
    - _Why this is good: You admit that setting up trinitycore itself might be too difficult for you, and you specify that your actual goal is to 'just have a playable server', which there might be alternatives for._

### Bad Question: Asking to avoid learning

Modding is difficult, workflows often take time to get into and frustrations can come at you at almost any time and in the most unpredictable forms.

Asking questions when stumbling into problems or even frustrations is not a bad thing on its own, but it's important to be wary of developing question-asking as a behavior to avoid doing your own research or experiments for anything that feels difficult or frustrating, because those are the only situations where you can effectively practice problem-solving yourself.

This has less to do with how many questions you ask, and more to do with how often you reach for asking without stopping to ask yourself if there is something you can try to teach yourself first, or an experiment you can attempt.

Aside from your very first steps into modding, if you frequently end up in situations where the only thing you can do is ask someone else, chances are you're attempting to do something that is too difficult for your current skill level, or that you are overwhelming yourself with too much frustration to learn anything effectively.

## Building Technical Proficiency

Even when narrowing down your modding scope to a single version of the game, like WoTLK, there are still tons of different file formats, conventions, programs and workflows to get used to.

## Strategies

This section will discuss how to actually handle problems in development, strategies to avoid them, and to identify and solve them effectively when they show up.

To make the sections more readable, I will use the following denotions:

- **Positive**: Means that we have a problem and are able to reproduce it.
- **Negative**: Means that we are unable to reproduce a problem.
- **Symptom**: Signs of a problem
- **Cause**: Root of a problem or subproblem
- **Regression**: Changes causing bugs or adverse effects to **previous** functionality.

### Losing a Positive

Once we have identified a _positive_ in our system, it may be tempting to try to get rid of by any means possible. However, a positive disappearing underneath our noses can sometimes be a bad thing, especially if we don't learn how it was introduced, and even worse if we don't learn how it disappeared.

### Dangers of 'Reasoning'

Being able to logically reason about modifications you've made to the game, how they should behave and what kind of problem a given set of symptoms often indicate is of course a very important skill to have as a modder. Many problems in the game are highly predictable, and something that you learn to pick up on the more you see them.

However, one very common mistake that beginners make is relying **too much** on reason alone to figure out what might be going wrong with their mods. This can often be ineffective for a few reasons:

- It often assumes that you have made your modification correctly on every step along the way
- It often assumes your tutorial is up-to-date and that you operate on correct information
- It often assumes that your problem stems from the problem you are _currently_ trying to solve, rather than something you did previously, or a combination of changes you are trying to make.
- It often assumes that the nature of symptoms are indicative of the nature of the problem.

### Version Control

Creating mods often involve editing large amount of different files, and even a single contained modification can contain a lot of complicated steps that can very easily go wrong along the way.

Version control are methods and tools used to create 'snapshots' of the state of our projects as we go to help us navigate and retrace the steps we've taken.

#### Tools

There are a few commonly used methods for version control, each with their own pros and cons.

##### 'Creating a copy of a file before editing it'

For quick edits and tests, it can sometimes be sufficient to just create a copy so you can easily revert any changes made to it if it inflicts a major regression. This can be good enough when working with a handful of `.dbc` files, but makes it hard to apply the more advanced version control strategies we will discuss below.

##### Git

Git is the most commonly used method for version control in WoW modding. It is a very powerful tool enabling most of the advanced 

- Version Control
    - Alternatives, Pros and Cons
    - Diff Views
    - Bisecting
    - Snapshotting
    - Squashing
    - Last working state
- Tracing and Debugging
    - When to trace
    - When to debug
- Divide and Conquer
    - Binary Search
    - Fuzzing
    - Corkscrew
    - Choosing violence
- Path of Balanced Resistance