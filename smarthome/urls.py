from django.contrib import admin
from django.urls import path
from rest_framework.routers import DefaultRouter

from metrics.views import MetricsViewSet


router = DefaultRouter()

router.register(r'metrics', MetricsViewSet, basename='metrics')

urlpatterns = router.urls

urlpatterns += [
    path('admin/', admin.site.urls),
]
