# Git Workflow Guide

## Github Token
To authenticate with GitHub, use the following token:
```
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
```

### Creating a Personal Access Token
To create a GitHub personal access token:
1. Go to your GitHub account settings.
2. Navigate to **Developer Settings > Personal Access Tokens > Tokens (classic)**.
3. Click **Generate new token**.
4. Select the appropriate scopes (e.g., `repo` for repository access).
5. Click **Generate token** and copy the token (you won’t be able to see it again).

**Note**: Use this token in place of your password when cloning or pushing to repositories via HTTPS.

## Cloning a Repository
Once a repository is created on GitHub, you can clone it to your local machine:
```bash
git clone <repository_url>
```
Example:
```bash
git clone https://github.com/bhupendra592/test.git
```

Navigate to the repository directory:
```bash
cd test/
pwd
```
Example output:
```
/home/bhupendra/DESD-IoT/Sept-2024/test
```

## Checking Repository Status
To check the status of your repository:
```bash
git status
```
Example output:
```
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

## Viewing Commit History
To view the commit history:
```bash
git log
```
Example output:
```
commit 53abbd99a982ea4dae3bd21aceb9f9719d3a821e (HEAD -> main, origin/main, origin/HEAD)
Author: Bhupendra Pratap Singh <bhupendra.jmd@gmail.com>
Date:   Sat Dec 28 09:41:06 2024 +0530

    Initial commit
```

## Making Changes and Committing
1. Stage changes for commit:
   ```bash
   git add .
   ```

2. Check the status of staged files:
   ```bash
   git status
   ```

3. Commit the changes with a message:
   ```bash
   git commit -m "added a new hello.py skeleton code"
   ```

4. Verify the commit by checking the log:
   ```bash
   git log
   ```

## Pushing Changes
Push the changes to the remote repository:
```bash
git push origin main
```

## Checking Remote URL
To check the remote URL of your repository:
```bash
git remote -v
```

## Summary of Commands
1. Clone repository:
   ```bash
   git clone <repository_url>
   ```
2. Navigate to repository:
   ```bash
   cd <repository_directory>
   ```
3. Check repository status:
   ```bash
   git status
   ```
4. Stage changes:
   ```bash
   git add .
   ```
5. Commit changes:
   ```bash
   git commit -m "<commit_message>"
   ```
6. Push changes:
   ```bash
   git push origin main
   ```
7. View commit history:
   ```bash
   git log
   ```
8. Update remote URL to SSH:
   ```bash
   git remote set-url origin git@github.com:<username>/<repository>.git
   ```


