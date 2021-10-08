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
# Ensure aws cli is installed and set up: https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-install.html
# The script requires a key pair to be set in AWS to identify instances and start new ones.
# Provisioning of keys is detailed here: https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html
# Note: The key parameter required by the script is the name of the key pair in AWS. 

# Start a new instance.
./scripts/avh_start -k <key pair> start

# Get instances status.
./scripts/avh_start -k <key pair> status

# Terminate an instance. If multiple instance are running, you must provide the instance ID.
./scripts/avh_start -k <key pair> status
```

3. Launch GitHub Self-Hosted Runner

```sh
# follow your repo's instructions to configure the github self hosted runner on the Arm Virtual Hardware ec2 instance
# https://github.com/exampleuser/my-ats-keyword.git/settings/actions/runners/new
 
# Login to the ami
> ssh ubuntu@<your-ec2-instance>
 
# Install runner software
> mkdir actions-runner && cd actions-runner
> curl -o <actions-runner.tar.gz -L https://github.com/actions/runner/releases/download/<version>/<action-runner>.tar.gz
> echo "<sha>  <action-runner>.tar.gz" | shasum -a 256 -c
> tar xzf ./<action-runner>.tar.gz
 
# Create, configure and run the runner
> ./config.sh --url https://github.com/exampleuser/my-ats-keyword --token <token>
> ./run.sh
 
# exit the ami and return shell back to your desktop
> exit
```

4. make a trivial (whitespace) code change and watch the code example compile and run test cases on Arm Virtual Hardware on your ec2 instance. 
   Please refer to Github actions [documentation](https://docs.github.com/en/actions) to make additional change to the workflow

```sh
# add whitespace to this file
> vi .github/workflows/build.yml
 
# git push it
> git add .github/workflows/build.yml
> git commit -m "initial arm virtual hardware github runner test"
> git push origin master
```

5. To update the application, a set of scripts is included to setup the environment, build applications, run them and test them. These scripts must be executed in the AVH AMI. 

```sh
# Synchronize git submodules, setup ML and apply required patches
./script/bootstrap.sh

# The python environment requires extra packages to sign the binaries
pip3 install click imgtool pytest

# Build the blinky or kws application
./script/build.sh <blinky|kws>

# Run the blinky or kws application
./script/build.sh <blinky|kws>

# Launch integration tests
pytest -s <blinky|kws>/tests
```

Alternatively, the projects can be build using [Keil MDK](https://www.arm.com/products/development-tools/embedded-and-software/keil-mdk).
`blinky.uvmpw` and `kws.uvmpw` contains respectively the `blinky` and `kws` project.  

# Setting up AWS connectivity

The KWS Demo will attempt to connect to AWS IOT and report ML inference results through an MQTT connection. For this to work you will need a [AWS Account](https://aws.amazon.com/) and setup an IoT thing and set credentials in the application.

## AWS account IoT setup

### Create an IoT thing for your device

1. Login to your account and browse to the [AWS IoT console](https://console.aws.amazon.com/iotv2/).
2. In the left navigation pane, choose **Manage**, and then choose **Things**.
3. If you do not have any IoT things registered in your account, the **You don’t have any things yet** page is displayed. If you see this page, choose **Register** a thing.
4. On the **Creating AWS IoT things** page, choose **Create a single thing**.
5. On the **Add your device to the thing registry** page, type a name for your thing (for example `MyThing`), and then choose **Next**. You will need to add the name later to your C code.
6. On the **Add a certificate for your thing** page, under **One-click certificate creation**, choose **Create certificate**.
7. Download your private key and certificate by choosing the **Download** links for each. Make note of the certificate ID. You need it later to attach a policy to your certificate.
8. Choose **Activate** to activate your certificate. Certificates must be activated prior to use.

### Create a policy and attach it to your thing

1. In the navigation pane of the AWS IoT console, choose **Secure**, and then choose **Policies**.
2. On the **Policies** page, choose **Create** (top right corner).
3. On the **Create a policy** page, enter a name for the policy. In the **Action** box, enter **iot:Connect**, **iot:Publish**, **iot:Subscribe**, **iot:Receive**. The **Resource ARN** box will be auto-filled with your credentials. Replace the part after the last semicolon (`:`) with `*`. Under **Effect**, check the **Allow** box. Click on **Create**.
4. In the left navigation pane of the AWS IoT console, choose **Secure**, and then choose **Certificates**. You should see the certificate that you have created earlier.
5. Click on the three dots in the upper right corner of the certificate and choose **Attach policy**.
6. In the **Attach policies to certificate(s)** window, enable the policy that you have just created and click **Attach**.

## Configure the application to connect to your AWS account

Edit `bsp/aws_configs/aws_clientcredential.h` file and set values of specified user defines.

`clientcredentialMQTT_BROKER_ENDPOINT`

Set this to the endpoint name of your amazon account. To find this go to the navigation pane of the [AWS IoT console](https://console.aws.amazon.com/iotv2/), choose **Settings**. On the **Settings** page, and copy the name of your **Endpoint** (such as `a3xyzzyx.iot.us-east-2.amazonaws.com`).

`clientcredentialIOT_THING_NAME`

Set this to the name of the thing you set (e.g. MyThing).

Next insert the keys that are in the certificates you have downloaded when you created the thing. Edit the file `bsp/aws_configs/aws_clientcredential_keys.h` replacing the existing keys with yours.

`keyCLIENT_CERTIFICATE_PEM`

Replace with contents from `<your-thing-certificate-unique-string>-certificate.pem.crt`.

`keyCLIENT_PRIVATE_KEY_PEM`

Replace with contents from `<your-thing-certificate-unique-string>-private.pem.key`.

`keyCLIENT_PUBLIC_KEY_PEM`

Replace with contents from `<your-thing-certificate-unique-string>-public.pem.key`.

## Observing MQTT connectivity

To see messages being sent by the application:
1. Login to your account and browse to the [AWS IoT console](https://console.aws.amazon.com/iotv2/).
2. In the left navigation panel, choose **Manage**, and then choose **Things**.
3. Select the thing you created, and open the **Activity** tab. This will show the application connecting and subscribing to a topic.
4. Click on the **MQTT test client** button. This will open a new tab.
5. The tab **Subscribe to a topic** should be already selected. Open the **Additional configuration** rollout.
6. In the topic filter field enter the topic name which is a concatenation of the name of your thing (set in clientcredentialIOT_THING_NAME) and `/ml/inference` (e.g. if you thing name is MyThing then it's `MyThing/ml/inference`)
7. In the **MQTT payload display** combo box select `Display payloads as strings (more accurate)`
8. Click the **Subscribe** button. The messages will be shown below.

# Replace DS-CNN

All the ML models supported by the [ML Embedded Eval Kit](All the models supported ) are available to applications. The first step to use another odule is to generate sources files from its labels and `.tflite` model.  

```sh
# Enter the ml example repository
cd lib/ml-embedded-evaluation-kit/

ML_GEN_SRC="generated/<model name>/src"
ML_GEN_INC="generated/<model name>/include"

mkdir -p $ML_GEN_SRC
mkdir -p $ML_GEN_INC

./lib/ml-embedded-evaluation-kit/resources_downloaded/env/bin/python3 scripts/py/gen_labels_cpp.py \
    --labels_file resources/<model name>/labels/<label file>.txt \
    --source_folder_path $ML_GEN_SRC \
    --header_folder_path $ML_GEN_INC \
    --output_file_name <model name>_labels 
./resources_downloaded/env/bin/python3 scripts/py/gen_model_cpp.py \
    --tflite_path resources_downloaded/<model name>/<model>.tflite \
    --output_dir $ML_GEN_SRC
```

Models available are present in `./lib/ml-embedded-evaluation-kit/resources_downloaded`.
Pre-integrated source code is available from the `ML Embedded Eval Kit` and can be browsed from `./lib/ml-embedded-evaluation-kit/source/use_case`. 

Integrating a new model means integrating its source code and requires update of the build files.

# ML Embedded Eval Kit

Philip Lewer to replace this text with a paragraph for ml embedded eval kit

# Future Enhancements
- [AWS Partner Device Catalog Listing](https://devices.amazonaws.com/) (leveraging Arm Virtual Hardware)
- cmake

# Other Resources

| Repository                                                                                                    | Description                                                                                                                                                                                                                        |
|---------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [Arm AI Ecosystem Catalog](https://www.arm.com/why-arm/partner-ecosystem/ai-ecosystem-catalog)                | Connects you to the right partners, enabling you to build the next generation of AI solutions                                                                                                                                      |
| [Arm ML Model Zoo](https://github.com/ARM-software/ML-zoo)                                                    | A collection of machine learning models optimized for Arm IP.                                                                                                                                                                      |
| [Arm Virtual Hardware Documentation](https://mdk-packs.github.io/VHT-TFLmicrospeech/overview/html/index.html) | Documentation for [Arm Virtual Hardware](https://www.arm.com/products/development-tools/simulation/virtual-hardware)                                                                                                               |
| [Arm Virtual Hardware Documentation](https://mdk-packs.github.io/VHT-TFLmicrospeech/overview/html/index.html) | Documentation for [Arm Virtual Hardware](https://www.arm.com/products/development-tools/simulation/virtual-hardware)                                                                                                               |
| [Arm CMSIS Build](https://arm-software.github.io/CMSIS_5/Build/html/index.html)                               | Documentation for the build system used by applications in this repository.                                                                                                                                                        |
| [AWS FreeRTOS](https://docs.aws.amazon.com/freertos/)                                                         | Documentation for AWS FreeRTOS.                                                                                                                                                                                                    |
| [AWS IoT](https://docs.aws.amazon.com/iot/latest/developerguide/what-is-aws-iot.html)                         | Documentation for AWS IoT.                                                                                                                                                                                                         |
| [Trusted Firmware-M](https://tf-m-user-guide.trustedfirmware.org/)                                            | Documentation for Trusted Firmware-M                                                                                                                                                                                               |
| Support                                                                                                       | A [community.arm.com](http://community.arm.com/) forum exists for users to post queries. INTERNAL NOTE →   they have – already set up on the test environment (link).  This will be moved to the live environment on 19th October. |

# License and contributions

The software is provided under the Apache-2.0 license. All contributions to software and documents are licensed by contributors under the same license model as the software/document itself (ie. inbound == outbound licensing). ATS-Keyword may reuse software already licensed under another license, provided the license is permissive in nature and compatible with Apache v2.0.

Folders containing files under different permissive license than Apache 2.0 are listed in the LICENSE file.