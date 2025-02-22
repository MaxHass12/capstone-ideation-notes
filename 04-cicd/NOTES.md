# 1. An Introduction To CI/CD

- Debugging code is hard, debugging configuration is way harder.

## 1.1 Getting Software To Production

- Many problems may arise when several developers are involved.

  1. "Works on my machine" problem.
  2. One dev can overwrite what other dev wrote.

- We need to find ways to work together and build software in a strictly defined way so that it's clear _exactly_ what will happen in any given scenario.

## 1.2 Some Useful Terms

### Branches

- Git allows multiple versions of the code to coexist without overwriting each other. This allows each developer to work on their own branch.
- Each branch is effectively a copy of `main` with some new features added or bug fixed, etc. Once the work on that branch is done, that branch is merged with the `main`. This allows each developer to work on their own set of changes without affecting others.
- Before merging, how does a developer know that his/her changes are compatible with `main` ie ( somebody else has not pushed anything incompatible to the `main`)

### Build

- In general it means preparing software to run on the platform it is supposed to run. (For eg - compiling the TS into JS, or bundling the React code). This step is much more complicated in compiled languages like C or Rust.

### Deploy

- Means putting the software where it needs to be for the end-user to use it.

- For example: In case of libraries it would be to pushing an npm package to package archive. Deploying a sofware can vary in complexity from automated deployment on `render` to more complicated on a VPS.

- Deployments can be significantly more complex if we have the requirements of **zero-downtime** or **database-migrations** (What laravel case study looked at)

## 1.3 What is Continuous Integration / Continous Deployment (CI/CD) ?

- Practise of integrating source code changes frequently and ensuring that the integrated code base `main` is in usable state.

- The steps involved in CI are:

  1. Lint
  2. Build
  3. Test
  4. Package (Put it all together in an easily movable batch)
  5. Deploy

- The above steps should be automated and setup in a way to allow for easier development and working together.

- **Continous Deployment** refers to keeping the `main` branch always deployable.

- The exact definitions are fuzzy and the distinction between them is murky. The term CI/CD is always used together.

## 1.4 Packaging and Deployment as part of CI/CD

- Some folks do not consider and Packaging and Deployment to be a part of CI/CD (??) but it makes a lot of sense to consider them as a part of CI/CD process.

## 1.5 Why is it important ?

- If we use the CI/CD process every time we merge to the `main` branch, then we know that the code will always run in production.
- If we only allow merges from local branches, when the local branch is updated with `main`, then we can be sure that 1 developer does not override anothers changes.

## 1.6 Important Principles ?

- CI/CD is not the goal. The goal is better, faster software development with fewer preventable bugs and better team cooperation. With that in mind, CI/CD should always be setup with the scope of the project.

### 1.6.1 You can think if CI as an answer to the following questions:

1. How to make sure that tests run on all code that will be deployed.
2. How to make sure that `main` branch is deployable all the time.
3. How to ensure that build will be consistent and the code will always run on the platform it is supposed to run.
4. How to ensure that the changes dont overwrite each other.
5. How to ensure that deployment happens automatically when changes are made to `main` branch.

### 1.6.2 Document behaviour

- There is an old joke that "a bug is an undocumented feature". We shoule try to avoid it.
- If the label _major_, _minor_ or _patch_ is important in the PR, then all devs should know about their meaning and when to put what label.
- Even after accounting for all possible cases, devs always do something "creative". In this case failure and notification to developer is the logical outcome.

### 1.6.3 Know the samethings happen everytime

- We might have an excellent and thorough test-suite, but it is useless if we dont run them before deploying.
- We need to make sure that the test-suite runs before the code is deployed, every single time.
- The core principle is that some steps are performed everytime in the same order.

### 1.6.4 Code Always Kept Deployable

- Having code that is always deployable makes life easy. Generally `main` branch contains the code running in production.
- In that case, if there is some error during deployment, the code will immediately fallback to the previous running version.

### 1.6.5 Knowing What code Is Deployed

- Generally `main` branch is in the production. What if it is not?

- Version Number, SHA sum, etc is used to identify which code is running in production.

## 1.7 Types of CI Setup

- Basically 2 kinds : self-hosted and cloud-hosted

### 1.7.1 Jenkins and other self-hosted setups

- Jenkins is the most popular option for self-hosted setups.

- With jenkins, the entire set up is under our control. Number of resources can be controlled, secrets are never exposed to anyone else.

- Downside is that jenkins is quite complicated to setup. We need to learn Jenkins own Domain Specific Language.

- With self hosted options, we pay for the hardware. What we do with the hardware does not matter.

### 1.7.1 Github Actions and cloud based solutions

- In a cloud hosted setup, the setup of environment is not something we have to worry about. Just involves putting a file in the repository.

- If you want to go beyond normal use (using GPUs), the cloud based option gets limiting. There is resource limitation in Clud based setups.

For a small to medium software project that does not have special requirements, a cloud based solution is sufficient. For larger project where more resources are needed or there are multiple teams, projects etc - a self hosted CI setup is required.

# 2. Github Actions

Github Actions work on the basis of **workflows**.

- A workflow is a series of **jobs** that are run when a triggering event happens.
- The jobs that are run contain instructions for what Github Actions must do.

Steps are:

1. Triggering event happens (push to `main`)
2. The workflow with trigger is executed
3. Cleanup

## 2.1 Basic Needs

To have CI operate on a repo we need

1. A repo
2. Some definition of what CI needs to do
3. Registering repo and instructions with the CI
4. CI needs to be able to access the repo
5. CI needs permissions to perform the actions it is instructed to do. For eg, if CI needs to do something in production environemnt, then CI needs access to credentials.

In the above Github actions have a great advantage. As Github provides both the repo and the CI platform, we just need to define the actions and github gets automatically aware of the workflow.

## 2.2 Getting Started With Workflows

- The core component of creating CI/CD pipeline with Github Actions is something called a Workflow.

- Workflows are process flows that we set up in our repo to run automated tasks like building, testing, linting, releasing, etc.

- Each workflow must have at least one Job. Jobs contain a series of steps to perform on individual tasks.

- Steps can vary from running a custom command to using pre-defined actions, thus the name Github actions. We can create custom actions our use any action published by the community.

- Github workflows must be recognized in `.github/Workflows`. Each workflow is its own separate file written in YAML.

- A basic worflow is made of 3 elements.

  1. `name`
  2. `on` - this is the trigger
  3. `jobs` At least one job which will contain a series of steps

- What all options are available for `on` for triggering a workflow ?

  - An _event_ on Github like someone pushing a commit or when an issue or a PR is created
  - A _scheduled event_ (in CRON syntax) happens.
  - An _externa event_ like in Slack happens

- In `jobs`, we can specify `runs-on` to let us decide the exact environment on which to run the job

- As the output of `ls -la` the virtual environment that runs our workflow does not have any code.

## 2.3 Setting up Lint, test and build steps

- It is important to specify the exact environment with `runs-on` key in the `jobs`. It is important to replicate the same environment in CI as production to avoid the issues when code runs differently in build and production.

- As we noted earlier we dont have any code inside our CI environment. For that, we need to define an **action** for that. An action is a reusable piece of code, like a function.

- Action can be defined in the repo in a separate file or we can use the one available in public repos.

The `uses` keyword tells a `step` to run a specific action.

- Here we use a public action `actions/checkout` to checkout the source code from the git repo to CI environment.

- Next we need to intall node runtime. `with` keyword is used to give param to the action.

- We use `wait-on` to wait before a certain action has completed.

- Running End To End testing in CI is nice because it gives us confidence that our application will run as intended. But the drawback is that it significantly slows down the process.

## 2.3.1 Lint

- The first step is to install dependencies. We generally give a `name` to the step - although that is optional and tell the exact command with `run`.

# 3. Deployment

- Its very simple to deploy software on Fly.io or render, but there is a great risk of deplying broken code to production.

## 3.1 Principles of Deploying Safely - Anything that can go wrong will go wrong

- Computers can crash, network partition can happen, some step during CI can fail, what if broken code gets published - can we roll back easily, what happens to HTTP requests which are in the pipeline the moment we change.

- Regardless of what happens our deployment system should never leave our software in a broken state. We should always know whats the status of the deployment process and roll back if any of the step fail.

- Silent failure is _very_ bad. Our deployment system should inform the devs of any errors.

## 3.2 What does a good deployment system do?

Minimum Requirements Are:

- Should make sure that all the requirements are run ie test, linting pass
- Should fail gracefull at any step of the deployment.
- Should never leave our software in a broken state.
- Should let us know when a failure happens. It is more important to notify about failure than success
  - Should allow us to roll back to a previous deployment
    - Rollback should be easier and less error-prone than a full deployment
    - Best base is automatic rollback
- Should handle the situation when a user sends an HTTP request just before or after deployment

Optional:

- Should be fast.
- No downtime during deployment ( this is separate from handling user requests just before and after deployment )

## 3.3 Health Checks

- If the app listens on the wrong port, it can still pass the CI/CD checks, be deployed but not work.

-  One option to prevent broken deployment is to use an HTTP level checks when the app is in production sending a request every few seconds to check whether the app is stil running.

- A canary deployment strategy is used to roll out new versions of application gradually and safely to a small subset of user or infrastructure before rolling it out to everyone. The canary group is then closely monitored using health checks, metrics, logs or user feedback.

- Generally http endpoint `/health` is used to send these checks.

# 4. Keeping Green

The `main` branch should always be green - ie all steps of deploy pipeline should pass. One way to do this is by avoiding pushing directly to main.

# 4.1 Working with PR

Using PR and getting the code reviewed by atleast 1 dev is a good idea. Senior devs can easily look into some issue, a reveiwer can have different perspective, other devs get familiar with the codebase, etc.

Github actions provide a trigger for PRs.   

# 4.2 Versioning

The most important purpose of versioning is to uniquely identify the software we are running and the code associated with it.

Ordering of versions is an important piece of info. 

# 4.2.3 Semantic Versioning

Semantic versioning is in the form of `{major}.{minor}.{patch}`.

- Changes the fix the functionality are `patch`
- Changes which change functionality are `minor`
- Change major functionality are `major`

`patch` and `minor` changes are back compatible, while `major` changes can be breaking.

# 4.2.3 Hash versioning

The version number in hash versioning is a hash which is derived from the content of the repo. In github, its the commit hash.

Hash versioning is never used with automation because of hash.

With Semantic versioning it is easier to say we want to roll back to `3.2.4`. With hash-versioning it is easier to decipher which commit caused the bug.

Hash versioning is also useful when commits are build into artifacts. For eg if the build of `1.2.3` fails then we can just make a new commit instead of dumping the `1.2.3` version number itself. 


