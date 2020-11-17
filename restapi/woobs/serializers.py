from rest_framework import serializers
from .models import DeviceReading


class DeviceReadingSerializer(serializers.ModelSerializer):
    class Meta:
        model = DeviceReading
        fields = ('id', 'date_time', 'temp', 'ph', 'device_id')