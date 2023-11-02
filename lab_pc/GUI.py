# Team 14 GUI code for ENGG2800 2022 Semester 1
import tkinter as tk
from tkinter import *
from tkinter import colorchooser
import serial
import serial.tools.list_ports

root = tk.Tk()

# This GUI adheres to the PEP 8 style guide

# the serialPort
serialPort = None

# response value
response = [None] * 4

# global variables to allow threading of data flow
colourRed = "#ee7942"
colourBlue = "#ee7942"
colourGreen = "#ee7942"

volumeMode = 0


# This class contains the main sections of the GUI
class App(object):
    # initialise function for this class
    def __init__(self, master):
        # mode setting
        self._modeSetting = ""
        # mode display setting
        self._modeDisplay = "JOYSTICK"
        # variable to set mode
        self._inputMode = 0
        # variable for colour
        self._colour = "#ee7942"
        self._redCode = "#ee7942"
        self._greenCode = "#ee7942"
        self._blueCode = "#ee7942"
        # volume variable
        self._currentValue = tk.DoubleVar()
        # joystick variable
        self._jstickData = 0
        # button variables
        self._buttonData = 0
        # volume variable
        self._volMode = 0

        # sets the title of the window and the size
        master.title("ENGG2800 Team 14 GUI")
        master.geometry("550x600")
        # the master frame
        self._master = master
        # the frame in which everything is to be stored
        self._mainframe = tk.Frame(master)
        self._mainframe.pack(fill=tk.BOTH, expand=1)

        # sets up the lower frame
        self.value_menu()

        # this is the comm-port frame at the top of the GUI
        self._portsframe = tk.Frame(self._mainframe, height=100, width=350)
        self._portsframe.grid(row=0, column=0, columnspan=3, sticky='nsew')
        # calls an askstring box and prompts the user to enter the com port
        self._portsframe.pack_propagate(0)

        # calls the 'serial' command to set up reading bits.
        self.com_port_selection()

        # this allows the main window to expand and resize correctly
        self._mainframe.grid_rowconfigure(0, weight=1)
        self._mainframe.grid_columnconfigure(0, weight=1)

        # temporary variable for now
        self._data = " "
        self.display_new_GUI_values()

    # This function connects the GUI to the com port
    def serial(self, com):
        global serialPort
        try:
            open(com)
            serialPort = serial.Serial(com, baudrate=9600, timeout=0.01,
                                       write_timeout=0)

            self.uart_send()
            # print messages to explain connection status
            print("You have successfully connected to: " + com)
        except serial.SerialException as e:
            if serialPort:
                if serialPort.portstr == com:
                    print("Already connected")
                    pass

                else:
                    serialPort = None
                    print("An Error Occurred")

            else:
                print("An Error Occurred")

    # Decides what is to be done with the the incoming data
    def received_data(self):
        # data received from serialPort
        self._data = serialPort.readline()
        if len(self._data) == 0:
            return

        self._buttonData = self._data[0]
        self._jstickData = self._data[1]

        self.display_new_GUI_values()
        self._data = ""

    # main function to handle sending and receiving data
    def uart_send(self):

        if not serialPort:
            print("Serial Not Connected")
            return

        else:
            self.received_data()

            if self._buttonData & (1 << 0):
                self._buttonCanvas.itemconfig(self._B1, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._B1, fill="red")
            if self._buttonData & (1 << 1):
                self._buttonCanvas.itemconfig(self._B2, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._B2, fill="red")
            if self._buttonData & (1 << 2):
                self._buttonCanvas.itemconfig(self._B3, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._B3, fill="red")
            if self._buttonData & (1 << 3):
                self._buttonCanvas.itemconfig(self._B4, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._B4, fill="red")
            if self._buttonData & (1 << 4):
                self._buttonCanvas.itemconfig(self._B5, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._B5, fill="red")
            if self._buttonData & (1 << 5):
                self._buttonCanvas.itemconfig(self._BP, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._BP, fill="red")
            if self._buttonData & (1 << 6):
                self._buttonCanvas.itemconfig(self._BC, fill="green")
            else:
                self._buttonCanvas.itemconfig(self._BC, fill="red")

            if self._jstickData == 0:
                self._jstickCanvas.itemconfig(self._middle, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._middle, fill="red")
            if self._jstickData == 1:
                self._jstickCanvas.itemconfig(self._down, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._down, fill="red")
            if self._jstickData == 2:
                self._jstickCanvas.itemconfig(self._up, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._up, fill="red")
            if self._jstickData == 4:
                self._jstickCanvas.itemconfig(self._right, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._right, fill="red")
            if self._jstickData == 8:
                self._jstickCanvas.itemconfig(self._left, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._left, fill="red")
            if self._jstickData == 6:
                self._jstickCanvas.itemconfig(self._upRight, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._upRight, fill="red")
            if self._jstickData == 10:
                self._jstickCanvas.itemconfig(self._upLeft, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._upLeft, fill="red")
            if self._jstickData == 5:
                self._jstickCanvas.itemconfig(self._downRight,
                                                fill="green")
            else:
                self._jstickCanvas.itemconfig(self._downRight, fill="red")
            if self._jstickData == 9:
                self._jstickCanvas.itemconfig(self._downLeft, fill="green")
            else:
                self._jstickCanvas.itemconfig(self._downLeft, fill="red")
       
        if self._colour:
            self._redCode = "0x" + self._colour[1] + self._colour[2]
            self._greenCode = "0x" + self._colour[3] + self._colour[4]
            self._blueCode = "0x" + self._colour[5] + self._colour[6]
            colourRed = int(self._redCode, 16)
            colourBlue = int(self._blueCode, 16)
            colourGreen = int(self._greenCode, 16)
        else:
            return

        volumeMode = self._volMode

        mode = self._inputMode
        if isinstance(volumeMode, str):
            val = int(volumeMode, 10)
        elif isinstance(volumeMode, int):
            val = volumeMode

        if mode == 0:
            if val < 128:
                val += 128
            else:
                pass

        message = bytearray([colourRed, colourBlue, colourGreen, val])
        serialPort.write(message)

        self.display_new_GUI_values()
        root.after(250, self.uart_send)

    # Toggle mode with button press
    def toggle_mode(self):

        mode = self._inputMode

        if mode == 0:
            self._inputMode = 1
            self._modeSetting = "DPAD"
            self._modeDisplay = "DPAD"

        elif mode == 1:
            self._inputMode = 0
            self._modeSetting = "JSTCK"
            self._modeDisplay = "JOYSTICK"
        else:
            pass

        self.display_new_GUI_values()
        self.uart_send()

    # open colour picker
    def pick_colour(self):
        self._colour = colorchooser.askcolor()[1]
        self.display_new_GUI_values()
        self.uart_send()

    # call function when volume is adjusted via slider
    def change_volume(self, val):
        self._volMode = val
        self.uart_send()

    # Update mode variable
    def update_mode(self, setting):
        self._modeSetting = str(setting)
        if setting == "DPAD":
            self._inputMode = 1
        elif setting == "JSTK":
            self._inputMode = 0
        else:
            pass

    # Updates the values on the GUI based on global variables
    def display_new_GUI_values(self):

        self._mode.config(text="MODE: " + str(self._modeDisplay))
        self._colourChange.config(text="Select Colour")
        self._displayColour.config(text="CHOSEN COLOUR", bg=self._colour)

    # Represents the button in the top frame that allows you to change the
    # communication port
    def com_port_selection(self):
        comPortSelected = tk.Label(self._portsframe,
                                   text="Selected comm-Port: ", fg='black')
        comPortSelected.grid(row=0, column=0, sticky='nsew')
        comPortSelected.config(font=("Courier", 20))

        """
        Note: port will not be visible until device is plugged in
        """

        # creates the options menu drop down
        default = StringVar(self._portsframe, "Please Select Port")
        ports = serial.tools.list_ports.comports()
        if ports != 0:
            OptionMenu(self._portsframe, default, *ports,
                       command=self.change_com_port) \
                .grid(row=0, column=1, columnspan=2, sticky='nsew')
        else:
            tk.Label(self._portsframe, text="No comm-ports available",
                     relief='groove') \
                .grid(row=0, column=1, columnspan=2, sticky='nsew')

    # Connects the com port to the serial
    def change_com_port(self, selection):

        self.serial(str(selection)[0:4])

    # Sets up the frame which displays the Values
    def value_menu(self):

        self._valueFrame = tk.Frame(self._mainframe,
                                    height=560, width=300, bg="sienna2",
                                    highlightthickness=1)
        self._valueFrame.grid(row=1, column=0, sticky='nsew')
        # propagate in order to stop the frame from dissapearing when a
        # label is inserted
        self._valueFrame.pack_propagate(0)

        # display current mode
        self._mode = tk.Label(self._valueFrame, text="MODE: ",
                              relief="groove", bg="sienna2")
        self._mode.pack(side=tk.TOP, pady=5)

        # mode toggle button
        self._modeChange = tk.Button(self._valueFrame, text="Toggle Mode",
                                     relief="groove",
                                     command=lambda: self.toggle_mode(),
                                     bg="sienna2")
        self._modeChange.pack(side=tk.TOP, pady=5)

        # colour chooser button
        self._colourChange = tk.Button(self._valueFrame, text="Select Colour",
                                       relief="groove",
                                       command=lambda: self.pick_colour(),
                                       bg="sienna2")
        self._colourChange.pack(side=tk.TOP, pady=5)

        # label to display chosen colour
        self._displayColour = tk.Label(self._valueFrame, text="Chosen Colour",
                                       relief="groove", bg=self._colour)
        self._displayColour.pack(side=tk.TOP, pady=5)

        # label to identify volume controls
        self._volumeScale = tk.Label(self._valueFrame, text="Adjust Volume:",
                                     bg="sienna2")
        self._volumeScale.pack(side=tk.TOP, pady=5)

        # slider to adjust volume
        self._volumeChange = tk.Scale(self._valueFrame, from_=0, to=127,
                                      orient="horizontal",
                                      variable=self._currentValue,
                                      command=self.change_volume)
        self._volumeChange.pack(side=tk.TOP, pady=5)

        # create canvas to display joystick position
        self._jstickCanvas = tk.Canvas(self._valueFrame, width=200, height=200,
                                       bg="sienna2")
        self._jstickCanvas.pack(pady=5)

        self._upLeft = self._jstickCanvas.create_oval(5, 65, 65, 5, fill="red")
        self._up = self._jstickCanvas.create_oval(70, 65, 130, 5, fill="red")
        self._upRight = self._jstickCanvas.create_oval(135, 65, 195, 5,
                                                       fill="red")
        self._left = self._jstickCanvas.create_oval(5, 130, 65, 70, fill="red")
        self._middle = self._jstickCanvas.create_oval(70, 130, 130, 70,
                                                      fill="green")
        self._right = self._jstickCanvas.create_oval(135, 130, 195, 70,
                                                     fill="red")
        self._downLeft = self._jstickCanvas.create_oval(5, 195, 65, 135,
                                                        fill="red")
        self._down = self._jstickCanvas.create_oval(70, 195, 130, 135,
                                                    fill="red")
        self._downRight = self._jstickCanvas.create_oval(135, 195, 195, 135,
                                                         fill="red")

        # label to show Button order
        self._buttonLayout = tk.Label(self._valueFrame,
                                      text="1  2  3  4  5  PLAYER  COIN",
                                      relief="groove", bg="sienna2", font=50)
        self._buttonLayout.pack(side=tk.TOP, pady=5)

        # create canvas to display button presses
        self._buttonCanvas = tk.Canvas(self._valueFrame, width=250, height=35,
                                       bg="sienna2")
        self._buttonCanvas.pack(pady=5)

        self._B1 = self._buttonCanvas.create_oval(5, 35, 35, 5, fill="red")
        self._B2 = self._buttonCanvas.create_oval(40, 35, 70, 5, fill="red")
        self._B3 = self._buttonCanvas.create_oval(75, 35, 105, 5, fill="red")
        self._B4 = self._buttonCanvas.create_oval(110, 35, 140, 5, fill="red")
        self._B5 = self._buttonCanvas.create_oval(145, 35, 175, 5, fill="red")
        self._BP = self._buttonCanvas.create_oval(180, 35, 210, 5, fill="red")
        self._BC = self._buttonCanvas.create_oval(215, 35, 245, 5, fill="red")


# Run program
app = App(root)
root.mainloop()
