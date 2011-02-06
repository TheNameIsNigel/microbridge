/*
 *
 */

#ifndef __usb__
#define __usb__

#include <stdint.h>
#include <stdbool.h>

// Device descriptor.
typedef struct {
	uint8_t bLength;				// Length of this descriptor.
	uint8_t bDescriptorType;		// DEVICE descriptor type (USB_DESCRIPTOR_DEVICE).
	unsigned int bcdUSB;			// USB Spec Release Number (BCD).
	uint8_t bDeviceClass;			// Class code (assigned by the USB-IF). 0xFF-Vendor specific.
	uint8_t bDeviceSubClass;		// Subclass code (assigned by the USB-IF).
	uint8_t bDeviceProtocol;		// Protocol code (assigned by the USB-IF). 0xFF-Vendor specific.
	uint8_t bMaxPacketSize0;		// Maximum packet size for endpoint 0.
	unsigned int idVendor;			// Vendor ID (assigned by the USB-IF).
	unsigned int idProduct;			// Product ID (assigned by the manufacturer).
	unsigned int bcdDevice;			// Device release number (BCD).
	uint8_t iManufacturer;			// Index of String Descriptor describing the manufacturer.
	uint8_t iProduct;				// Index of String Descriptor describing the product.
	uint8_t iSerialNumber;			// Index of String Descriptor with the device's serial number.
	uint8_t bNumConfigurations;		// Number of possible configurations.
} usb_deviceDescriptor;

// Configuration descriptor.
typedef struct
{
	uint8_t bLength;               // Length of this descriptor.
	uint8_t bDescriptorType;       // CONFIGURATION descriptor type (USB_DESCRIPTOR_CONFIGURATION).
	unsigned int wTotalLength;          // Total length of all descriptors for this configuration.
	uint8_t bNumInterfaces;        // Number of interfaces in this configuration.
	uint8_t bConfigurationValue;   // Value of this configuration (1 based).
	uint8_t iConfiguration;        // Index of String Descriptor describing the configuration.
	uint8_t bmAttributes;          // Configuration characteristics.
	uint8_t bMaxPower;             // Maximum power consumed by this configuration.
} usb_configurationDescriptor;

// Interface descriptor.
typedef struct
{
	uint8_t bLength;               // Length of this descriptor.
	uint8_t bDescriptorType;       // INTERFACE descriptor type (USB_DESCRIPTOR_INTERFACE).
	uint8_t bInterfaceNumber;      // Number of this interface (0 based).
	uint8_t bAlternateSetting;     // Value of this alternate interface setting.
	uint8_t bNumEndpoints;         // Number of endpoints in this interface.
	uint8_t bInterfaceClass;       // Class code (assigned by the USB-IF).  0xFF-Vendor specific.
	uint8_t bInterfaceSubClass;    // Subclass code (assigned by the USB-IF).
	uint8_t bInterfaceProtocol;    // Protocol code (assigned by the USB-IF).  0xFF-Vendor specific.
	uint8_t iInterface;            // Index of String Descriptor describing the interface.
} usb_interfaceDescriptor;

/* Endpoint descriptor structure */
typedef struct
{
	uint8_t bLength;               // Length of this descriptor.
	uint8_t bDescriptorType;       // ENDPOINT descriptor type (USB_DESCRIPTOR_ENDPOINT).
	uint8_t bEndpointAddress;      // Endpoint address. Bit 7 indicates direction (0=OUT, 1=IN).
	uint8_t bmAttributes;          // Endpoint transfer type.
	unsigned int wMaxPacketSize;        // Maximum packet size.
	uint8_t bInterval;             // Polling interval in frames.
} usb_endpointDescriptor;

// USB Setup Packet.
typedef struct
{
	uint8_t bmRequestType; //   0      Bit-map of request type
	uint8_t bRequest; //   1      Request
	uint16_t wValue; //   2      Depends on bRequest
	uint16_t wIndex; //   4      Depends on bRequest
	uint16_t wLength; //   6      Depends on bRequest
} usb_setupPacket;

/**
 * USB endpoint.
 */
typedef struct
{
    // Endpoint address. Bit 7 indicates direction (out=0, in=1).
	uint8_t address;

	// Endpoint transfer type.
	uint8_t attributes;

	// Maximum packet size.
    uint16_t maxPacketSize;

    // The max3421e uses these bits to toggle between DATA0 and DATA1.
    uint8_t sendToggle;
    uint8_t receiveToggle;

} usb_endpoint;

/**
 * USB device.
 */
typedef struct
{
	// Device address.
	uint8_t address;

	// Indicates whether this device is active.
	uint8_t active;

	// Endpoints.
	usb_endpoint control;
	usb_endpoint bulk_in, bulk_out;

	// First supported language (for retrieving Strings)
	uint16_t firstStringLanguage;

} usb_device;

void usb_init();
void usb_poll();

int usb_getDeviceDescriptor(usb_device * device, usb_deviceDescriptor * descriptor);
int usb_printDeviceInfo(usb_device * device);
int usb_initDevice(usb_device * device, int configuration);

usb_device * usb_getDevice(uint8_t address);

void usb_initEndPoint(usb_endpoint * endpoint, uint8_t address);

int usb_bulkRead(usb_device * device, uint16_t length, uint8_t * data);
int usb_bulkWrite(usb_device * device, uint16_t length, uint8_t * data);

#endif
