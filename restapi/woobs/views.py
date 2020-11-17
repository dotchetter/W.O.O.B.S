from django.shortcuts import render
from rest_framework import viewsets
from .models import DeviceReading
from .serializers import DeviceReadingSerializer


class DeviceReadingView(viewsets.ModelViewSet):
    queryset = DeviceReading.objects.all()
    serializer_class = DeviceReadingSerializer
