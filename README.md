# ImageDecomposerC

<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** georgerapeanu, ImageDecomposerC, twitter_handle, a.rapeanu49@gmail.com, Image decomposer, project_description
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/georgerapeanu/ImageDecomposerC">
    <img src="logo.jpg" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Image decomposer</h3>

  <p align="center">
    A tiny app that tries its best to replicate an given image.
    <br />
    <a href="https://github.com/georgerapeanu/ImageDecomposerC/docs"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/georgerapeanu/ImageDecomposerC/demo">View Demo</a>
    ·
    <a href="https://github.com/georgerapeanu/ImageDecomposerC/issues">Report Bug</a>
    ·
    <a href="https://github.com/georgerapeanu/ImageDecomposerC/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)
This started as a fun little python project(see <a href="https://github.com/georgerapeanu/ImageEllipseDecomposer">this repository</a>), but eventually, due to my desire to learn opencv for C++(using a tiny bit of oop), to see how much faster it would be, to learn cmake and to pottentially use docker, I decided to rewrite it in C++. This app's objective is to try to aproximate as good as it can a given image, using various shapes and colors to achive this. Currently, this repository has one downside: altough the python projects is slower and can only use ellipses to cover images, it stores this ellipses in svg format, which may have some applications.

Here's a blank template to get started:
**To avoid retyping too much info. Do a search and replace with your text editor for the following:**
`georgerapeanu`, `ImageDecomposerC`, `a.rapeanu49@gmail.com`, `Image decomposer`, `project_description`


### Built With

* [Cmake](https://cmake.org/)
* [Opencv](https://opencv.org/)
* [Flask](https://flask.palletsprojects.com/en/2.0.x/)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* cmake
  ```sh
     sudo apt-get install cmake
  ```
* opencv
  run ```installOpencv.sh``` anywhere in your filesystem.
* flask
  ```sh
     sudo apt-get install python3
     sudo apt-get -y install python3-pip
     pip3 install opencv-python
     pip3 install flask_wtf
     pip3 install wtforms
     pip3 install werkzeug
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/georgerapeanu/ImageDecomposerC.git
   ```
2. Compile the project
   ```sh
   mkdir build
   cd build
   cmake ../
   make .
   ```

<!-- USAGE EXAMPLES -->
## Usage

To run the app, you simply have to run ```python3 server.py```. The app will use 2 ports.
```localhost:8000``` will display the current image being processed.
```localhost:8001``` is the admin interface. You can select here the image and all the additional settings through a form.

_For more examples, please refer to the [Documentation](https://github.com/georgerapeanu/ImageDecomposerC/docs)_



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/georgerapeanu/ImageDecomposerC/issues) for a list of proposed features (and known issues).


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. However, currently I would like this project to remain more of a personal one.
However, if you still want to contribute, there might be a chance that your pull request is accepted. In that case, follow the next steps:

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Project Link: [https://github.com/georgerapeanu/ImageDecomposerC](https://github.com/georgerapeanu/ImageDecomposerC)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/georgerapeanu/ImageDecomposerC.svg?style=for-the-badge
[contributors-url]: https://github.com/georgerapeanu/ImageDecomposerC/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/georgerapeanu/ImageDecomposerC.svg?style=for-the-badge
[forks-url]: https://github.com/georgerapeanu/ImageDecomposerC/network/members
[stars-shield]: https://img.shields.io/github/stars/georgerapeanu/ImageDecomposerC.svg?style=for-the-badge
[stars-url]: https://github.com/georgerapeanu/ImageDecomposerC/stargazers
[issues-shield]: https://img.shields.io/github/issues/georgerapeanu/ImageDecomposerC.svg?style=for-the-badge
[issues-url]: https://github.com/georgerapeanu/ImageDecomposerC/issues
[license-shield]: https://img.shields.io/github/license/georgerapeanu/ImageDecomposerC.svg?style=for-the-badge
[license-url]: https://github.com/georgerapeanu/ImageDecomposerC/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/georgerapeanu
