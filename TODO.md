- [ ] Remove imgui

# Phase 1 - simple circuits

Toplevel
- [x] Create object infrastructure
  - [x] Graphic library interface
- [x] Draw toplevel (board)
- [x] Drag toplevels around

Board wiring
- [x] Wire management (top board only)

Component creation
- [x] Create components: transistor, button, led
- [x] Component parts
  - Board placement (size, can rotate, keypress to place)
  - Configuration (change behaviour through UI elements, mock only for now)
  - Load image (from file or XBM) and draw
  - Simulation
  - Serialization

Board serialization:
- [x] Component serialization

Components in board:
- [x] Add/remove components/wires to board
- [x] Rotate components

# Phase 2 - simulation

- [ ] Testing infrastructure
- [ ] Serialization
- [ ] Compilation
- [ ] Simulation
- [ ] New components
  - [ ] NPN, PNP, VCC, wire crossing

# Phase 3 - circuits QOL

Board creation
- [ ] Resize board
- [ ] Select components
- [ ] Cut/Copy/paste chucks
- [ ] Add text to board
- [ ] Save/load boards
  - [ ] Board serialization
  - [ ] Game serialization

UI
- [ ] Menu bar
- [ ] Save/load dialog

# Phase 4 - Sidebar

UI
- [ ] Sidebar
  - [ ] Text
  - [ ] Text formatting
  - [ ] Images
  - [ ] Buttons
  - [ ] Tests

# Phase 5 - advanced wiring

- [ ] Board lower wiring
- [ ] Bus
- [ ] Adapter

# Phase 6 - ICs + customization

Board
- [ ] Lua circuits
- [ ] ICs
  - [ ] IC placement/removal
  - [ ] Fixed behaviour
  - [ ] Lua
- [ ] Subcircuits

# Phase 7 - Game

UI
- [ ] Title screen
- [ ] Game levels

Levels
- [ ] Create levels

# Phase 8 - Custom toplevels

- [ ] Video
- [ ] Audio
- [ ] Inputs
