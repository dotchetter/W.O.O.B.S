from django.db import models


class DeviceReading(models.Model):
    """
    Represents a reading from a device.
    """
    date_time = models.DateTimeField(auto_now=True, blank=True)
    temp = models.FloatField()
    ph = models.FloatField()
    device_id = models.CharField(max_length=255)

    def __str__(self):
        return f"device_id: {self.device_id} date: {self.date_time}" \
               f"temp: {self.temp} ph: {self.ph}"