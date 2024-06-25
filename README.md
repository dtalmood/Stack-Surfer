# Stack-Overflow-Search-Engine
Have you ever felt that the stackoverflow search results do not match what you are looking for? 

This app was made inorder to make searching for question you want to see easier. 

This application has full User Authetnication via MongoDB and once you create your account you can use the search engine. 

Features

**Sort:** Provides user options sort the results by either. 

  1. Views
  2. Answer Count
  3. Score

**Tags:** Allows users to have speicifc tags to ensure results relate more closely to what you are looking for. 

**Filters:** Any infomration you do or do not care to see can be simply adjusted via the filters which can remove the following from search result 
  1. Acceptance Rate
  2. Answer Count
  3. Creation Date
  4. Reputation
  5. Score
  6. Views

**Express Instalation:**

First, install xcode command line tools (this allows for installing necesary libraries)

```xcode-select --install ```

Second, Donwload Homebrew 

``` /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" ```


After last command completes, copy the two commands in section labled **next step** below is example of what the commands will look like

```Example 1: (echo; echo 'eval "$(/opt/homebrew/bin/brew shellenv)"') >> /Users/YOUR_USER_PROFILE/.zprofile```

```Example 2: eval "$(/opt/homebrew/bin/brew shellenv)"```


After words Download the File "express.sh" (be sure your in directly where this file is located after donwloading) and run 2 commands below inorder 

``` chmod +x express.sh```


```./express.sh``` 

Once done in terminal run the following command to start up Mongo DB(this will allow you the client to connect to server local host 27017)


```brew --prefix mongodb/brew/mongodb-community ```

```mongod --config /usr/local/etc/mongod.conf```

Now, in a new terminal, run MongoDB shell to connect to the MongoDB server:

```mongo --host localhost --port 27017 ```










  




