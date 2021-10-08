/*
 * FreeRTOS V202012.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

// IMPORTANT FIXME: this files content changes on a device / iot thing basis

/*
 * PEM-encoded client certificate.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUJQ+OjgWxOPXruxLz8EP5NWS68wswDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDgyNTExMjY0\n"\
"OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAO7BA+4kdXLfY+zCrV2e\n"\
"Xwvb2VghkilT3kS/9/1aA9AwbLHCpWelXj2bKLLB1jt8gNObCz/3OhInweihjgsM\n"\
"BLEhgvT/fF7v6YHsnwiTj6r5Ui9xy69jgQpYh7Gm5s+GydlqSD4Z82GZdU4Xizb0\n"\
"Xp2rfp0zKjq0Sp2ZKvUQeurSTfxuE3n8/hWGmvdPFRRnV1a9SKT2Jd/NbTZklfcZ\n"\
"6Y43FYvvlzTae6Z5QYkJ6UHx8icTgm9NNNExp953Mguq4PUaLM7dfZ6586/4B1U3\n"\
"2m/FMvERf5UdO84gxPT89Wa5+WpKZIXfBkJDIEnajOepV10sNc9ubh3cxsVlrsQO\n"\
"EQ8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUPEmRsgyCJ10rIUr6U9dgig6OgsYwHQYD\n"\
"VR0OBBYEFL0u6/eFu2jAXesd3uiOhstLi1BsMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCA8BNDUVMtozydF55ectkUjPss\n"\
"pTYxBqYDPj6czzNcsfuluYldJtL2JOZU58kyXYeWTf/FNdoNjoAvCL13+6LmsOog\n"\
"pnMzzT3FAl8ZWSOkvhJ3u66q7FftSCwEoHGYT/pO29np9DwXIKh2NIZRlqz8bLjD\n"\
"m2Q6QGMol9yLpJNVBFYlqDY1JurTXmQhJx0KiCf9u4q3BolDEp90nftOjjctg9+1\n"\
"blI8dOiRJtJXCdq5VV4PnfTr6z3HNZOyewJts2ENGrBB0hmnfMMhm1qDd5EJsuM0\n"\
"H0cxO+pE3Zkt5zNACA5lBgUFkpSISGR3WnnoLT3EXRQGAdH973qGTjpHyBbY\n"\
"-----END CERTIFICATE-----\n"


/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpAIBAAKCAQEA7sED7iR1ct9j7MKtXZ5fC9vZWCGSKVPeRL/3/VoD0DBsscKl\n"\
"Z6VePZsossHWO3yA05sLP/c6EifB6KGOCwwEsSGC9P98Xu/pgeyfCJOPqvlSL3HL\n"\
"r2OBCliHsabmz4bJ2WpIPhnzYZl1TheLNvRenat+nTMqOrRKnZkq9RB66tJN/G4T\n"\
"efz+FYaa908VFGdXVr1IpPYl381tNmSV9xnpjjcVi++XNNp7pnlBiQnpQfHyJxOC\n"\
"b0000TGn3ncyC6rg9Roszt19nrnzr/gHVTfab8Uy8RF/lR07ziDE9Pz1Zrn5akpk\n"\
"hd8GQkMgSdqM56lXXSw1z25uHdzGxWWuxA4RDwIDAQABAoIBAF95Ibg2Lh0shYnk\n"\
"42y/auSUGpqqegc6uXQmi+Vs/H9hDeYbnwcOUtwx0pmA98k75Uw5AMuocjlWWq1L\n"\
"BUEXojyu2O5dx/8y0t6Yn5PPZjEJmDrOt5PAJ5bahhCdXEj6bncZkB/9Qpzxv73l\n"\
"nk7wc3F7ZZs5HZbyB7Bz0oDDAVQq1TBFAUiQTLVcdO41F1Z+ij7+sRlVUI84/soX\n"\
"Qip+HGjuM5c108O4Cfclc8fxdWp+GCZ1zoMPheSFRYwZ/7TL0lTSiyVvxET4XrjT\n"\
"Zh9Hfa/jYNMTWCBDT6QmoxN1vJ1//T2qAEltFNkmzf/cQn/WU1czmVixgXuOwqM4\n"\
"GI6Vh8ECgYEA+9m/I9jOBoE3ShNr9nE84GcuDZTqRDG12ofKOjdfT9keODKqkEzZ\n"\
"Nidc6Tz2WcsF2ywD62iNH01Lnsn4FANJq1MO4SBzsYVDRgZK5WrtrlPMfseilFEI\n"\
"cM707q9WbNFa0vbWSwjyaJVvIcrfYRLWRyOojN2wP/vu3CLN4B3K8OECgYEA8rAH\n"\
"qqjHDuPXpoNqGAc5gCvjvu+Dfxefz/9RkljL+DTSkPc4ZY56yxFM3Xw2cJZQFRmJ\n"\
"5m9SDa45LutMRlbODq4eeyVknPW2/xSSDhapWJI8lkkjydUlrvT9Z9ltrkmBKA5v\n"\
"scrc09kpEMQjhVkNDniR3hnacrw6da2xRoy6D+8CgYEA5T8srK2hw+wE7unE4Xvs\n"\
"BPwGwJgnslFpjnUCUIGswZsJ1e/QsC8znQaxnSE/wTZ7qyhinPr7Ul3ikrSXm2fu\n"\
"vAOLzMLkbNe4B9qcfD4cAg4HW/POeqFURJMuAsIZsk3TFatYHs8TEL3Nff4T3WHv\n"\
"KKw9tZPp5iQmJb2Mlw+ndiECgYEA4ELcgs6+S7suH3hWxOeAMjnclidcu0gIbTvB\n"\
"lFwr+CxP3JgnbGlyfU56Wj2bTQUJ8cWM0f1StMOnofzbmjBC7/vkvOV8CTNirGrE\n"\
"4PH+AZP5GuNxh+RIk1lfBeU9Xo4cJPjaLFCLKdUGBrFJJcN5tkKigLwhSl84ImCk\n"\
"bc5Dbc8CgYBzeSwOD8ApbYoENyPoTGoO80U/qcfFNEL/cUapViez6GKNGvOmYXWM\n"\
"QzI6GUAn2+C3fRFqOBBHvhzfQ6kn9e67vk78h3AAW9zGsh4rVPLXt/4v3SmzVsWe\n"\
"B4Ui8JNiZpKu7K9IbB/DwHDXDUFV7rt8LTqjoBexeUz0AVWPPubrig==\n"\
"-----END RSA PRIVATE KEY-----\n"


/*
 * PEM-encoded Just-in-Time Registration (JITR) certificate (optional).
 *
 * If used, must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  ""


#define keyCLIENT_PUBLIC_KEY_PEM \
"-----BEGIN PUBLIC KEY-----\n"\
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA7sED7iR1ct9j7MKtXZ5f\n"\
"C9vZWCGSKVPeRL/3/VoD0DBsscKlZ6VePZsossHWO3yA05sLP/c6EifB6KGOCwwE\n"\
"sSGC9P98Xu/pgeyfCJOPqvlSL3HLr2OBCliHsabmz4bJ2WpIPhnzYZl1TheLNvRe\n"\
"nat+nTMqOrRKnZkq9RB66tJN/G4Tefz+FYaa908VFGdXVr1IpPYl381tNmSV9xnp\n"\
"jjcVi++XNNp7pnlBiQnpQfHyJxOCb0000TGn3ncyC6rg9Roszt19nrnzr/gHVTfa\n"\
"b8Uy8RF/lR07ziDE9Pz1Zrn5akpkhd8GQkMgSdqM56lXXSw1z25uHdzGxWWuxA4R\n"\
"DwIDAQAB\n"\
"-----END PUBLIC KEY-----\n"


#define keyCA1_ROOT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"\
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"\
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"\
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"\
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"\
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"\
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"\
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"\
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"\
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"\
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"\
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"\
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"\
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"\
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"\
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"\
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"\
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"\
"-----END CERTIFICATE-----"


#define keyCA3_ROOT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIBtjCCAVugAwIBAgITBmyf1XSXNmY/Owua2eiedgPySjAKBggqhkjOPQQDAjA5\n"\
"MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24g\n"\
"Um9vdCBDQSAzMB4XDTE1MDUyNjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkG\n"\
"A1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJvb3Qg\n"\
"Q0EgMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABCmXp8ZBf8ANm+gBG1bG8lKl\n"\
"ui2yEujSLtf6ycXYqm0fc4E7O5hrOXwzpcVOho6AF2hiRVd9RFgdszflZwjrZt6j\n"\
"QjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBSr\n"\
"ttvXBp43rDCGB5Fwx5zEGbF4wDAKBggqhkjOPQQDAgNJADBGAiEA4IWSoxe3jfkr\n"\
"BqWTrBqYaGFy+uGh0PsceGCmQ5nFuMQCIQCcAu/xlJyzlvnrxir4tiz+OpAUFteM\n"\
"YyRIHN8wfdVoOw==\n"\
"-----END CERTIFICATE-----"


#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
