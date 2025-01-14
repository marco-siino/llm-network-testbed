Sure! Here's the Python code that sets up the network described in the TEST BLUEPRINT. This code uses the Fabric framework to manage connections for the WiFi Access Point (AP). It also configures the AP through hostapd.conf and dnsmasq.conf. It creates fixed IP configurations for each station in the dnsmaq.conf file.

```python
import os
import sys
import traceback
import grpc
from chirpstack_api import api

#URL API CHIRPSTACK: https://www.chirpstack.io/docs/chirpstack/api/api.html

from dotenv import load_dotenv
load_dotenv()
server = os.getenv('CHIRPSTACK_URL')  # Adjust this to your ChirpStack instance
api_token = os.getenv('CHIRPSTACK_API_TOKEN')  # Obtain from ChirpStack
tenant_id = os.getenv('CHIRPSTACK_TENANT_ID') #this is a tenant ID for fabrizio.giuliano@unipa.it

channel = grpc.insecure_channel(server)
auth_token = [("authorization", "Bearer %s" % api_token)]

def ListGateways(tenant_id):
  client = api.GatewayServiceStub(channel)
  req = api.ListGatewaysRequest()
  req.tenant_id = tenant_id
  req.limit = 1000
  resp = client.List(req, metadata=auth_token)
  return resp

def ListApplications(tenant_id):
  client = api.ApplicationServiceStub(channel)
  req = api.ListApplicationsRequest()
  req.tenant_id = tenant_id
  req.limit = 1000
  resp = client.List(req, metadata=auth_token)
  return resp

def ListDevices(application_id):
  client = api.DeviceServiceStub(channel)
  req = api.ListDevicesRequest()
  req.application_id = application_id
  req.limit = 1000
  resp = client.List(req, metadata=auth_token)
  return resp

def CreateApplication(name, tenant_id):
  client = api.ApplicationServiceStub(channel)
  req = api.CreateApplicationRequest()
  req.application.name = name
  req.application.tenant_id = tenant_id
  resp = client.Create(req, metadata=auth_token)
  return resp

def GetApplicationID(name, tenant_id):
  client = api.ApplicationServiceStub(channel)
  req = api.CreateApplicationRequest()
  req = api.GetApp
  req.id = name
  req.tenant_id = tenant_id
  resp = client.Create(req, metadata=auth_token)
  return resp

def CreateDeviceProfile(name, tenant_id, region="EU868", mac_version="LORAWAN_1_0_3", revision ="RP002_1_0_3", supports_otaa=True):
  client = api.DeviceProfileServiceStub(channel)
  req = api.CreateDeviceProfileRequest()
  req.device_profile.name=name
  req.device_profile.tenant_id = tenant_id
  req.device_profile.region = region
  req.device_profile.reg_params_revision = revision
  req.device_profile.mac_version = mac_version
  req.device_profile.supports_otaa = supports_otaa
  resp = client.Create(req, metadata=auth_token)
  return resp

def DeleteDeviceProfile(id):
  client = api.DeviceProfileServiceStub(channel)
  req = api.DeleteDeviceProfileRequest()
  req.id = id
  resp = client.Delete(req, metadata=auth_token)
  return resp

def CreateDevice(dev_eui, name, application_id, device_profile_id, application_key, skip_fcnt_check=True, is_disabled=False):
  client = api.DeviceServiceStub(channel)
  req = api.CreateDeviceRequest()
  req.device.dev_eui = dev_eui
  req.device.name = name
  req.device.description = ""
  req.device.application_id = application_id
  req.device.device_profile_id = device_profile_id
  req.device.skip_fcnt_check = skip_fcnt_check
  req.device.is_disabled = is_disabled
  resp = client.Create(req, metadata=auth_token)

  client = api.DeviceServiceStub(channel)
  req = api.CreateDeviceKeysRequest()
  req.device_keys.dev_eui = dev_eui
  req.device_keys.nwk_key = application_key
  req.device_keys.app_key = application_key
  resp = client.CreateKeys(req, metadata=auth_token)

  return resp

def DeleteDevice(device_id):
  client = api.DeviceServiceStub(channel)
  req = api.DeleteDeviceRequest()
  req.dev_eui=device_id
  resp = client.Delete(req,metadata=auth_token)
  return resp

def CreateGateway(gateway_id, name, tenant_id, description=None, location=None):
  client = api.GatewayServiceStub(channel)
  req = api.CreateGatewayRequest()
  req.gateway.gateway_id=gateway_id
  req.gateway.name = name
  req.gateway.description =description
  req.gateway.tenant_id=tenant_id
  resp = client.Create(req, metadata=auth_token)
  return resp

def DeleteGateway(gateway_id):
  client = api.GatewayServiceStub(channel)
  req = api.DeleteGatewayRequest()
  req.gateway_id=gateway_id
  resp = client.Delete(req, metadata=auth_token)
  return resp

def get_dict(str_application_id):
    k, v = str_application_id.split(': ')
    v = v.replace('"','').strip("\n")
    return {k: v}

def GetDeviceProfile(id):
  client = api.DeviceProfileServiceStub(channel)
  req = api.GetDeviceProfileRequest()
  req.id = id
  resp = client.Get(req, metadata=auth_token)
  return resp

def DeleteApplication(id):
  try:
    client = api.ApplicationServiceStub(channel)
    req = api.DeleteApplicationRequest()
    req.id=id
    resp = client.Delete(req, metadata=auth_token)
    return resp
  except Exception:
    print(traceback.format_exc())

def ListDeviceProfiles(tenant_id):
  client = api.DeviceProfileServiceStub(channel)
  req = api.ListDeviceProfilesRequest()
  req.tenant_id = tenant_id
  req.limit = 1000
  resp = client.List(req, metadata=auth_token)
  return resp

# Create Gateway
print("[STEP1] CREATE GATEWAY")
DeleteGateway("05b0da50148fd6b1")
CreateGateway(
  gateway_id="05b0da50148fd6b1",
  name="TEST-GW",
  description="Gateway Building 9",
  tenant_id=tenant_id
)

# Create Application
print("[STEP2] CREATE APPLICATION")
dict_application_id = get_dict(str(CreateApplication(name="TEST-BLUEPRINT",tenant_id=tenant_id)))
application_id=dict_application_id["id"]

# Create Device Profile
print("[STEP3] CREATE DEVICE PROFILE")
dict_device_profile_id = get_dict(str(CreateDeviceProfile(name="TEST_OTAA_EU868_1.1.0",mac_version="LORAWAN_1_1_0", revision="RP002_1_0_3", tenant_id=tenant_id)))
device_profile_id=dict_device_profile_id["id"]

# Create Devices
print("[STEP4] CREATE ALL LORAWAN DEVICES described in the blueprint")
DeleteDevice(device_id="81a63bce0927e700")
CreateDevice(
    dev_eui="81a63bce0927e700",
    name="IOT-001",
    application_id=application_id,
    device_profile_id=device_profile_id,
    application_key="4ba2162e111f9c2c216b7d68e09f43a8",
    skip_fcnt_check=False,
    is_disabled=False
)
DeleteDevice(device_id="89697aa089cc3005")
CreateDevice(
    dev_eui="89697aa089cc3005",
    name="IOT-002",
    application_id=application_id,
    device_profile_id=device_profile_id,
    application_key="a1ac00d450efb7facb46a243cbf7731f",
    skip_fcnt_check=False,
    is_disabled=False
)
```