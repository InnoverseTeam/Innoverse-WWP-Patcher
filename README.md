# Innoverse-WWP-Patches
Patcher of Innoverse for Wara Wara Plaza on Wii U.

# How to use it ?
- First, you need to install Aroma on your Wii U (use this video https://www.youtube.com/watch?v=3O6Zbj36d-I&t=20s).

# How to build ?
- First, need to create Docker Image `docker build . -t innoverse-wwp-builder`.
- And after, compile the project with `docker run -it --rm -v .:/app innoverse-wwp-builder`.
