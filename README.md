# Introduction

[Arm IoT Total Solutions](https://confluence.arm.com/www.arm.com/solutions/iot/total-solutions-iot) provides a complete solution designed for specific use-cases, leaving developers to focus on what really matters – innovation and differentiation across diverse and varied use cases. It has everything needed to simplify the design process and streamline product development, including hardware IP, software, real-time OS support, machine learning (ML) models, advanced tools such as the new Virtual Hardware Targets, application specific reference code and support from the world’s largest IoT ecosystem.  

# Configurations

This repo contains Arm's first [IoT Total Solution](https://confluence.arm.com/www.arm.com/solutions/iot/total-solutions-iot), "Keyword Detection".  It provides general-purpose compute and ML workload use-cases, including an ML-based keyword recognition example that leverages the DS-CNN model from the [Arm Model Zoo](https://github.com/ARM-software/ML-zoo). The software supports multiple configurations of the Arm Corstone™-300 subsystem, incorporating the Cortex-M55 processor and Arm Ethos™-U55 microNPU.  This total solution provides the complex, non differentiated secure platform software on behalf of the ecosystem, thus enabling you to focus on your next killer app.  This repo also supports a GitHub runner ci/cd workflow right out of the box which leverages [Arm Virtual Hardware](https://www.arm.com/products/development-tools/simulation/virtual-hardware), a simulation environment that enables software development without the need of physical SoCs.  The source code in this repo supports several configurations of the software, all of which are AWS IoT Core (OTA, etc.) enabled right out of the box.  Instructions for using non-default configurations are provided in the below table.

| # | default | description                                                                                              | .github/workflows/build.yml code change |   |
|---|---------|----------------------------------------------------------------------------------------------------------|-----------------------------------------|---|
| 1 |         | general purpose compute application (blinky application running on the m55 processor only)               | tbd                                     |   |
| 2 |         | keyword detection application (running on the m55 only)                                                  | tbd                                     |   |
| 3 |   YES   | keyword detection application (running on the m55+u55)                                                   | tbd                                     |   |
| 4 |         | instructions for replacing the keyword model and application code with your own custom application/model | tbd                                     |   |

# Quick Start
Follow these simple steps to use this code example's default configuration #3 keyword detection application.

1. Mirror this repo
```sh
# create a mirror (assumes new repo is already created https://docs.github.com/en/articles/creating-a-new-repository)
> git clone --bare https://github.com/ARM-software/ATS-Keyword
> cd ATS-Keyword
> git push --mirror https://github.com/exampleuser/my-ats-keyword.git
 
# clone your new repo
> git clone https://github.com/exampleuser/my-ats-keyword.git
 
# optionally remove the original repo from your hard drive
> cd ..
> rm -rf ATS-Keyword
```

2. Launch Arm Virtual Hardware Instance

```sh
# TBD
```

3. Launch GitHub Self-Hosted Runner

```sh
# follow your repo's instructions to configure the github self hosted runner on the Arm Virtual Hardware ec2 instance
# https://github.com/exampleuser/my-ats-keyword.git/settings/actions/runners/new
 
# Login to the ami
> ssh ubuntu@<your-ec2-instance>
 
# Install runner software
> mkdir actions-runner && cd actions-runner
> curl -o actions-runner-osx-x64-2.283.2.tar.gz -L https://github.com/actions/runner/releases/download/v2.283.2/actions-runner-osx-x64-2.283.2.tar.gz
> echo "d7d026b9bf1cb3f133cf53e79c71c0458a82b3f2bdb0a8859cd386ae18ee7c4a  actions-runner-osx-x64-2.283.2.tar.gz" | shasum -a 256 -c
> tar xzf ./actions-runner-osx-x64-2.283.2.tar.gz
 
# Create, configure and run the runner
> ./config.sh --url https://github.com/exampleuser/my-ats-keyword --token <token>
> ./run.sh
 
# exit the ami and return shell back to your desktop
> exit
```

4. make a trivial (whitespace) code change and watch the code example compile and run test cases on Arm Virtual Hardware on your ec2 instance

```sh
# add whitespace to this file
> vi .github/workflows/build.yml
 
# git push it
> git add .github/workflows/build.yml
> git commit -m "initial arm virtual hardware github runner test"
> git push origin master
```

# Replace DS-CNN

```sh
# pseudo cli/commands/steps to replace the keyword model with another model
# example can use a model from the arm model zoo
# steps should be validated by arm prior to release
```

# ML Embedded Eval Kit

Philip Lewer to replace this text with a paragraph for ml embedded eval kit

# Future Enhancements
- [AWS Partner Device Catalog Listing](https://devices.amazonaws.com/) (leveraging Arm Virtual Hardware)
- cmake

# Other Resources

| Repository                                                                                                    | Description                                                                                                                                                                                                                        |   |   |   |
|---------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---|---|---|
| [Arm AI Ecosystem Catalog](https://www.arm.com/why-arm/partner-ecosystem/ai-ecosystem-catalog)                | Connects you to the right partners, enabling you to build the next generation of AI solutions                                                                                                                                      |   |   |   |
| [Arm ML Model Zoo](https://github.com/ARM-software/ML-zoo)                                                    | A collection of machine learning models optimized for Arm IP.                                                                                                                                                                      |   |   |   |
| [Arm Virtual Hardware Documentation](https://mdk-packs.github.io/VHT-TFLmicrospeech/overview/html/index.html) | Documentation for [Arm Virtual Hardware](https://www.arm.com/products/development-tools/simulation/virtual-hardware)                                                                                                               |   |   |   |
| Support                                                                                                       | A [community.arm.com](http://community.arm.com/) forum exists for users to post queries. INTERNAL NOTE →   they have – already set up on the test environment (link).  This will be moved to the live environment on 19th October. |   |   |   |

# License and contributions

The software is provided under the Apache-2.0 license. All contributions to software and documents are licensed by contributors under the same license model as the software/document itself (ie. inbound == outbound licensing). ATS-Keyword may reuse software already licensed under another license, provided the license is permissive in nature and compatible with Apache v2.0.

Folders containing files under different permissive license than Apache 2.0 are listed in the LICENSE file.