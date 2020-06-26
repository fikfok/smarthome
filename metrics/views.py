from django.shortcuts import render
from rest_framework import viewsets

from models import Metrics
from permissions import IsArduino
from serializers import MetricsSerializer


class MetricsViewSet(viewsets.ModelViewSet):
    permission_classes = [IsArduino]
    queryset = Metrics.objects.all()
    serializer_class = MetricsSerializer

