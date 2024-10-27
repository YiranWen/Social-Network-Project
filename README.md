# Social Network Simulation Project

## Overview
This C++ project simulates a social network where users can create posts, comment, and interact with other users within a network structure. It includes functionalities for handling user data, posts, comments, and relationships within the network, as well as an interface for viewing and managing interactions.

## Features
- **User Management**: Create, view, and manage users in the network with attributes such as user ID, name, birth year, and unique interactions.
- **Post and Comment Functionality**: Allows users to create posts and add comments to others' posts, with public and private options.
- **Network Interactions**: Enables connections among users, facilitating a simulated network structure of relationships.
- **GUI Integration**: Provides a user interface (using Qt) for seamless interaction and demonstration of network functionalities.

## Files Overview
- `comment.cpp` / `comment.h`: Handles operations related to comments on posts.
- `post.cpp` / `post.h`: Manages post creation, editing, and properties.
- `network.cpp` / `network.h`: Implements network structure and user connections.
- `social_network.cpp`: Main program logic managing social network simulation.
- `user.cpp` / `user.h`: User class for creating and managing user data.
- **Qt Project Files**:
  - `HW4.pro`: Project configuration file for building the application in Qt.
  - `postdialog.cpp` / `postdialog.h`: Code for handling dialog-based interactions with posts in the GUI.
  - `socialnetworkwindow.cpp` / `socialnetworkwindow.h`: Code for the main GUI window managing network interactions.
- **Data Files**:
  - `UsersPosts.txt`: Sample posts associated with different users.
  - `PostComments.txt`: Sample comments linked to specific posts.
  - `users.txt`: Contains sample user data, including names and relationships.
  - `metadata.yml`: Metadata configuration file.
  - `ProjectDemonstration.mp4`: A video demonstrating the project’s functionality.

## Setup and Installation
1. **Install Qt**: Ensure you have Qt installed as the GUI uses Qt libraries.
2. **Compile**: Use the `.pro` file (`HW4.pro`) to compile the project in Qt Creator.
3. **Run**: Launch the application from Qt Creator to view the social network simulation in action.

## Usage
- **Create and View Posts**: Users can create posts, mark them as public or private, and view posts from other users.
- **Comment on Posts**: Add comments to posts and view comments from other users.
- **Manage Connections**: View and interact with a simulated network of connected users.
- **Demo Video**: View `ProjectDemonstration.mp4` for a walkthrough of the main functionalities.

## Future Enhancements
- Expand user interaction options, such as likes or shares.
- Implement additional privacy settings.
- Improve network visualization for a more comprehensive view of user interactions.

## License
This project is open for educational and non-commercial purposes.
