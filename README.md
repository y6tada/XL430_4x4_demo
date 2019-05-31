# Note
This program requires some revision to the Arduino library, DynamixelShield version 0.0.5. Then, you have to add a function "setJointExtendedMode" and edit some structure variables in `Documents/Arduino/library/DynamixelShield/src/DynamixelShield.h` and `DynamixelShield.cpp`.

# Change of cpp file
* Insert this program from line 496
~~~
bool DynamixelShield::setJointExtendedMode(uint8_t id)
{
  bool ret;
  uint8_t data;
  dxl_model_t dxl_model;

  ret = getDxlModelFromID(id, &dxl_model);

  if (ret == true)
  {
    if (dxl_model.protocol == DXL_PACKET_VER_2_0)
    {
      data = dxl_model.op_joint_extended_mode;      
      ret = write(id, dxl_model.op_mode.addr, (uint8_t *)&data, dxl_model.op_mode.length, 100);
    }
  }

  return ret;
}
~~~
* Insert this program in line 1037
~~~
      p_model->op_joint_extended_mode = 4;
~~~

# Change of Header file
* Insert this program in line 82
~~~
  uint8_t          op_joint_extended_mode;
~~~
* Insert this program in line 148
~~~
  bool setJointExtendedMode(uint8_t id);
~~~
