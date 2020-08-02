from rest_framework import serializers

from metrics.models import Metrics


class MetricsSerializer(serializers.ModelSerializer):
    class Meta:
        model = Metrics
        fields = ('dttm_label', 'temperature', 'carbon_dioxide',)

    dttm_label = serializers.DateTimeField(format='%d.%m.%Y %H:%M:%S', source='dttm')
