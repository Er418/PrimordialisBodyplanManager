# Unskill3d Bodyplan Manager

A small utility for installing and uninstalling bodyplan files for **Primordialis Demo**.

---

## Overview

All files related to **Unskill3d Bodyplan Manager** are stored under the following directory, 
created automatically on the first bodypack installation:
```%Steam folder%/steamapps/common/Primordialis Demo/unskill3d_bodyplan_manager```
### Scripts

1. **`install_bodyplans.exe`**
    - Creates a backup of the current bodyplans if none exists, then installs a custom bodypack from the `body plans` folder located in the same directory as the script.
      - Backup is created in `/Primordialis Demo/unskill3d_bodyplan_manager/backup`
      

2. **`uninstall_bodyplans.exe`**
    - **Function**: Reverts bodyplans to the backed-up default files, removing the custom bodypack.
      - Uses backup from `/Primordialis Demo/unskill3d_bodyplan_manager/backup`

### Notes

- All modifications only apply to bodyplans visible in the game. Unused assets, imported plans, and personal creations remain unaffected.
- **Custom Bodypack Name**: Set the bodypack name in `config.json` under the `bodypack_name` key. (Currently affects only displayed name during installation, but may be useful if and when I implement proper manager functionality)

---

## Folder Structure

Your bodypack should be organized in the following format:
```
[Your bodypack name]
├── body plans 
│ ├── fish.bod
│ ├── [other bodyplan assets] 
├── config.json 
├── install_bodyplans.exe 
└── uninstall_bodyplans.exe
```

---

## License

This project is licensed under the MIT License.
