package com.harun.lightsofmyroom.Adapter;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.harun.lightsofmyroom.R;

import java.util.ArrayList;
import java.util.Set;

/**
 * Created by harun on 29/09/2017.
 */

public class PairedDeviceAdapter extends BaseAdapter {
    private Context context;
    private ArrayList arrPairedDevices;


    public PairedDeviceAdapter(Context context,Set<BluetoothDevice> pairedDevices){
        this.context = context;
        arrPairedDevices = new ArrayList(pairedDevices);
    }

    @Override
    public int getCount() {
        return arrPairedDevices.size();
    }

    @Override
    public BluetoothDevice getItem(int position) {
        return (BluetoothDevice) arrPairedDevices.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View row = convertView;
        DeviceHolder holder;

        if (row == null){
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            row = inflater.inflate(R.layout.row_device_name, parent, false);
            holder = new DeviceHolder(row);
            row.setTag(holder);

        } else {
            holder = (DeviceHolder) row.getTag();
        }

        holder.tvDeviceName.setText(getItem(position).getName());
        holder.tvDeviceAddress.setText(getItem(position).getAddress());


        return row;
    }

    private class DeviceHolder{
        private TextView tvDeviceName;
        private TextView tvDeviceAddress;

        public DeviceHolder(View view){
            tvDeviceName = view.findViewById(R.id.tvDeviceName);
            tvDeviceAddress = view.findViewById(R.id.tvDeviceAddress);
        }
    }
}
