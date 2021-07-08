from smbus import SMBus
import time
bus = SMBus(1)
slaveAddress = 0x69                         # Slave Address of Arduino
messageLength = 32                          # Message Length
dataIn = ""                                 # Message from Arduino
dataOut = "1234"                            # Message for Arduino

RFID_ON = False                             # RFID activation flag
RFID_LENGTH = 8                             # Number of bytes per tag
DISP_ON = False                             # Food activation flag
DISP_AMOUNT = "150"                         # Amount of food to dispense in grams
TIME_ON = False                             # Flag para enviar horas
FOOD_ON = False                             # Flag para receber ração comida
FOOD_LENGTH = 3                             # Tamanho da palavra a receber
AQUA_ON = False                             # Flag para o deposito de agua
AQUA_LENGTH = 1                             # Tamanho da palavra a receber
STOW_ON = False                             # Flag para ração no deposito de comida
STOW_LENGTH = 5                             # Tamanho da palavra a receber

timer_a = time.time()
timer_b = time.time()

def StringToBytes(str):
    bytes = []
    for c in str:
            bytes.append(ord(c))            #Converts to asccii
    return bytes

def BytesToString(bytes):
    string = ""
    for b in bytes:
          # if b == chr(255) :              #Prevents extra info to be added to the string
          #     break
            string += chr(b)                #Converts from asccii
  # return string.replace(chr(255),'')      #Returns string with spaces instead of symbols
    return string                           #Returns string

while True:
    if time.time() - timer_a > 20: # 20 Seconds
        timer_a = time.time()
        print('20 seconds')
        RFID_ON = !RFID_ON

   # if time.time() - timer_b > 30: #30 Seconds
   #     timer_b = time.time()

    if RFID_ON:
        bus.write_block_data(slaveAddress, 0x00, StringToBytes("RFID")) # Send a rfid message
        dataIn = bus.read_i2c_block_data(slaveAddress, 0, RFID_LENGHT) #Request RFID TAG
        print(BytesToString(dataIn))    #Print in the rfid tag string

    if DISP_ON:     # Send a amount of food to dispense
        bus.write_block_data(slaveAddress, 0x00, StringToBytes("DISP" + FOOD_AMOUNT))

    if TIME_ON:     # Send a time
        TIME        = time.gmtime()[0:6]
        TIME_YEAR   = str(TIME[0])
        TIME_MONTH  = str(TIME[1]) if TIME[1]>=10  else '0' + str(TIME[1])
        TIME_DAY    = str(TIME[2]) if TIME[2]>=10  else '0' + str(TIME[2])
        TIME_HOUR   = str(TIME[3]) if TIME[3]>=10  else '0' + str(TIME[3])
        TIME_MINUTE = str(TIME[4]) if TIME[4]>=10  else '0' + str(TIME[4])
        TIME_SECOND = str(TIME[5]) if TIME[5]>=10  else '0' + str(TIME[5])
        TIME_MSG    = TIME_YEAR+TIME_MONTH+TIME_DAY+TIME_HOUR+TIME_MINUTE+TIME_SECOND
        bus.write_block_data(slaveAddress, 0x00, StringToBytes("TIME" + ))

    if FOOD_ON:
        bus.write_block_data(slaveAddress, 0x00, StringToBytes("FOOD"))
        dataIn = bus.read_i2c_block_data(slaveAddress, 0, FOOD_LENGTH)
        print(BytesToString(dataIn))

    if AQUA_ON:
        bus.write_block_data(slaveAddress, 0x00, StringToBytes("AQUA"))
        dataIn = bus.read_i2c_block_data(slaveAddress, 0, AQUA_LENGTH)
        print(BytesToString(dataIn))

    if STOW_ON:
        bus.write_block_data(slaveAddress, 0x00, StringToBytes("STOW"))
        dataIn = bus.read_i2c_block_data(slaveAddress, 0, STOW_LENGTH)
        print(BytesToString(dataIn))


        # dataIn = bus.read_i2c_block_data(slaveAddress, 0, messageLength)        #Request data
        # print(dataIn)                           #Print data in bytes (like it is received via i2c)
        # print(BytesToString(dataIn))            #Print in a string
        # print(StringToBytes(dataOut))           #Print in bytes what we are going to send
        # print(BytesToString(StringToBytes(dataOut)))    #Print string we are going to send
        # time.sleep(0.2)
        # bus.write_block_data(slaveAddress, 0x00, StringToBytes(dataOut))        #Write data
        # time.sleep(5)
