from rest_framework import viewsets

from metrics.models import Metrics
from metrics.pagination import MetricsPagination
from metrics.permissions import IsArduino
from metrics.serializers import MetricsSerializer


class MetricsViewSet(viewsets.mixins.ListModelMixin,
                     viewsets.mixins.CreateModelMixin,
                     viewsets.GenericViewSet):
    permission_classes = [IsArduino]
    queryset = Metrics.objects.all().order_by('-dttm')
    serializer_class = MetricsSerializer
    pagination_class = MetricsPagination


