#from django.conf import settings
from rest_framework.permissions import BasePermission


class IsArduino(BasePermission):
    """
    Доступ только для сервиса Arduino
    """
    def has_permission(self, request, view):
        return request.META.get('HTTP_API_KEY') == 'i_am_arduino'  # settings.ARDUINO_API_KEY

